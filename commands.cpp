//		commands.c
//********************************************
#include "commands.h"
extern HistoryCommands history;
extern char* previousCd;
extern ListOfJobs* jobsList;
extern string L_Fg_Cmd;
extern int L_Fg_Cmd_Pid;
//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{
	char* cmd ;
	char* args[MAX_ARG];
	//char pwd[MAX_LINE_SIZE];
	const char* delimiters = " \t\n";
	int num_arg = 0;
	bool illegal_cmd = FALSE; // illegal command
    cmd = strtok(lineSize, delimiters);
    
	if (cmd == NULL)
		return 0; 
   	args[0] = cmd;
    int i=1;
    while ( i<MAX_ARG)
	{
		args[i] = strtok(NULL, delimiters);
        if (args[i] != NULL){
			num_arg++; 
        }
        i++;
	}
/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
	if (!strcmp(cmd, "cd") ) 
	{
        if(num_arg != 1){
            illegal_cmd = TRUE;
        }
        else{
            char* currDir;
            if(( currDir=getcwd(NULL, 0)) == NULL){
                perror("");
                exit(1);
            }
            if(!strcmp("-", args[1])){
                if(previousCd != NULL){
                    chdir(previousCd);
                    cout << previousCd << endl;
                    previousCd = currDir; // CHECK VALGRIND !
                }
            }
            else{
                int resultChdir = chdir(args[1]);
                if(!resultChdir){
                    previousCd = currDir;
                }
                else if (resultChdir && errno == ENOENT){
                    cout << "smash error:> \"" << args[1] << "\"-path not found" << endl;
                }
            }
        }
	} 
	
	/*************************************************/
	else if (!strcmp(cmd, "pwd")) 
	{
        if(num_arg)
        {
            illegal_cmd = TRUE;
        }
        else{
            char pwd_command[MAXPWD];
            if (getcwd(pwd_command, sizeof(pwd_command)) == NULL){
              perror("");
                exit(1);
            }
            else
                printf("%s\n", pwd_command);
        }
	}
	
	/*************************************************/
	/*************************************************/
	
	else if (!strcmp(cmd, "jobs")) 
	{
        if (num_arg) {
            illegal_cmd=TRUE;
        }
        else{
            //jobsList->addJobToList(134, "test");
            jobsList->listJobsPrint();
        }
	}
	/*************************************************/
	else if (!strcmp(cmd, "showpid")) 
	{
        if(num_arg){
            illegal_cmd = TRUE;
        }
        else{
            printf("smash pid is %d\n",getpid());
        }
	}
	/*************************************************/
    else if (!strcmp(cmd,"kill")){
        if(num_arg != 2 || args[1][0] != '-'){
            illegal_cmd = TRUE;
        }
        else{
            int idJob = atoi(args[2]);
            int pidJob = jobsList->pidFromId(idJob);
            if(pidJob == PIDNULL){
                cout << "smash error: > kill " << idJob<<" – job does not exist" << endl;
                return 0;
            }
            int sigNum = atoi(args[1]+1); //remove '-'
            bool verifSignal = sendSignal(pidJob, sigNum, args[1]+1);
            if (!verifSignal) {
                cout << "smash error: > kill " << idJob << " – cannot send signal" << endl;
                return 0;
            }
        }
    }
    /*************************************************/
	else if (!strcmp(cmd, "fg")) 
	{
        if(num_arg > 1){
            illegal_cmd = TRUE;
        }
        else{
            int pid;
            
            if(!num_arg){
                pid = jobsList->pidLastJob();
            }
            else{
                pid = jobsList->pidFromId(atoi(args[1]));
            }
            if(pid == PIDNULL){
                return 0;
            }
            
            jobsList->printNameOfJob(pid);
            
            if(jobsList->jobIsStopped(pid)==TRUE){
                jobsList->setJobStoppedFromPid(pid,FALSE);
                sendSignal(pid,SIGCONT,"SIGCONT");
            }
            int status;
            waitpid(pid,&status,WUNTRACED);
        }
	} 
	/*************************************************/
	else if (!strcmp(cmd, "bg")) 
	{
        if(num_arg>1){
            illegal_cmd = TRUE;
        }
        else{
            int pid;
            if (num_arg) {
                pid = jobsList->pidFromId(atoi(args[1]));
            }
            else{
                pid = jobsList->pidLastJobStopped();
            }
            if(pid==PIDNULL){
                return 0;
            }
            jobsList->setJobStoppedFromPid(pid,FALSE);
            jobsList->printNameOfJob(pid);
            sendSignal(pid,SIGCONT,"SIGCONT");
        }
	}
	/*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
        if (num_arg > 1) {//too many arguments
            illegal_cmd = TRUE;
        }
        else if (num_arg == 1) {
            if (strcmp(args[1], "kill"))
                illegal_cmd = TRUE;
            else {////quit kill
                jobsList->listKillAll();
                exit(0);
            }//end quit kill
        }// end 1 argument
        else if (num_arg == 0) {// the command was only quit
            //pid_t my_pid = getpid();
            //kill(my_pid, SIGKILL);
            exit(0);
        }// end only quit
    }//end quit
   		
	
    
    /*************************************************/
    else if (!strcmp(cmd,"history"))
    {
        if(num_arg){
            illegal_cmd = TRUE;
        }
        else{
            history.printHistory();
        }
    }
    else if(!strcmp(cmd,"mv")){
        if (num_arg != 2){
            illegal_cmd = TRUE;
        }
        else{
            int res=rename(args[1],args[2]);
            if(res){
                cout<<args[1]<<" has been renamed to "<<args[2] << endl;
            }
            else{
                   perror("renaming failed");
            }
        }
    }
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString);
	 	return 0;
	}
	if (illegal_cmd == TRUE)
	{
		printf("smash error: > \"%s\"\n", cmdString);
		return 1;
	}
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
					// Add your code here (error)
					
            perror("");
            break;
            
        	case 0 :
                	// Child Process
               		setpgrp();
            execv(args[0],args);
            //if the child process still alive there is an error
            perror("");
            exit(1);
            break;
			        // Add your code here (execute an external command)
					
			default:
                	// Add your code here
            int status;
            L_Fg_Cmd = string(args[0]);
            L_Fg_Cmd_Pid = pID;
            waitpid(L_Fg_Cmd_Pid, &status, WUNTRACED);
            //reinitilization
            L_Fg_Cmd = "";
            L_Fg_Cmd_Pid = PIDNULL;
	}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
	//char ExtCmd[MAX_LINE_SIZE+2];
	//char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
        return 0;
	} 
	return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{

	char* Command;
	const char* delimiters = " \t\n";
	char *args1[MAX_ARG];
    int i = 0, num_arg = 0;
    char tmp[MAX_LINE_SIZE] ;
    strcpy(tmp, lineSize);
    tmp[strlen(lineSize)-1]='\0';
    Command = strtok(tmp, delimiters);
    if (Command == NULL)
        return 0;
    args1[0] = Command;
    for (i=1; i<MAX_ARG; i++)
    {
        args1[i] = strtok(NULL, delimiters);
        if (args1[i] != NULL)
            num_arg++;
    
       }
    //lineSize[strlen(lineSize)-2] == '&'
	if ((!strcmp(args1[num_arg],"&")) && (num_arg!=0))
	{
       
        //lineSize[strlen(lineSize)-2] = '\0';
		// Add your code here (execute a in the background)
        if(Command != NULL){
            int pid = fork();
            if(pid == 0){
                setpgrp();
                execv(Command,args1);
                perror("execv");
                exit(1);
            }
            else if (pid>0){
                jobsList->addJobToList(pid,string(Command));
                return 0;
            }
            else{
                perror("");
            }
        }
		/* 
		your code
		*/
		
	}
    for(int i=0;i<MAX_ARG;i++){
        args1[i]=NULL;
    }
	return -1;
}

