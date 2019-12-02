// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"
extern string L_Fg_Cmd;
extern int L_Fg_Cmd_Pid;
extern ListOfJobs* jobsList;
//********************************************
// function name: setSignalHandler
// Description: initialize the signal handler
// Parameters: no
// Returns: true - success,0 - failure
//**************************************************************************************
bool setSignalHandler()
{
    struct sigaction siga_cntlc,siga_cntlz;
    siga_cntlc.sa_handler = &handler_cntlc;
    siga_cntlz.sa_handler = &handler_cntlz;
    sigset_t maskSet_cntlc,maskSet_cntlz;
    if((sigfillset(&maskSet_cntlc)) || (sigfillset(&maskSet_cntlz))){
        return FALSE;
    }
    siga_cntlc.sa_mask = maskSet_cntlc;
    siga_cntlz.sa_mask = maskSet_cntlz;
    if(sigaction(SIGINT,&siga_cntlc,NULL) || sigaction(SIGTSTP, &siga_cntlz,NULL)){
        return FALSE;
    }
    return TRUE;
}
//********************************************
// function name: handler_cntlc
// Description: handle the signal send by CTRL+C
// Parameters: signum
// Returns:NO
//**************************************************************************************
void handler_cntlc(int signum)
{
    
    if(L_Fg_Cmd_Pid == PIDNULL){
        return;
    }
    jobsList->removeJobFromPid(L_Fg_Cmd_Pid);
    bool verifSendSignal = sendSignal(L_Fg_Cmd_Pid, SIGINT, "SIGINT");
    if(!verifSendSignal){
        exit(1);
    }
    L_Fg_Cmd_Pid = PIDNULL;
    L_Fg_Cmd = "";
    int status;
    wait(&status);
    return;
    
}
//********************************************
// function name: handler_cntlz
// Description: handle the signal send by CTRL+Z
// Parameters: signum
// Returns:NO
//**************************************************************************************
void handler_cntlz(int signum)
{
    if(L_Fg_Cmd_Pid == PIDNULL){
        return;
    }
    bool verifSendSignal = sendSignal(L_Fg_Cmd_Pid, SIGTSTP, "SIGTSTP");
    if(!verifSendSignal){
        exit(1);
    }
    jobsList->addJobToList(L_Fg_Cmd_Pid, L_Fg_Cmd);
    jobsList->setJobStoppedFromPid(L_Fg_Cmd_Pid, TRUE);
    L_Fg_Cmd_Pid = PIDNULL;
    L_Fg_Cmd = "";
    return;
}
//********************************************
// function name: sendSignal
// Description: When a signal is send , print wich one to who
// Parameters: pid of the receiver , the number of the signal and its name
// Returns:true - success,false - failure
//**************************************************************************************
bool sendSignal(int pid , int sig , const char* sigName)
{
    printf("smash > signal %s was sent to pid %d\n", sigName,pid);
    
    if(kill(pid, sig)==-1){
        perror("");
        return FALSE;
        
    }
    return TRUE;
}
