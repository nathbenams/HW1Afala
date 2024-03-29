/*	smash.c
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commands.h"
#include "signals.h"
#include "Jobs.h"
#include "ListOfJobs.h"
#include "HistoryCommands.h"
#define MAX_LINE_SIZE 80
#define MAXARGS 20


HistoryCommands history;

string L_Fg_Cmd;
int L_Fg_Cmd_Pid; //for the signals use

ListOfJobs* jobsList; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
char lineSize[MAX_LINE_SIZE];

char* previousCd;
//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    char cmdString[MAX_LINE_SIZE]; 	   

	
	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	 /* add your code here */
	if (!setSignalHandler())
    {
        perror("");
        exit(-1);
    }
	/************************************/
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	//set your signal handlers here
	/* add your code here */

	/************************************/

	/************************************/
	// Init globals 
    ListOfJobs list_ = ListOfJobs();
    jobsList = &list_;
    history = HistoryCommands();
    
    L_Fg_Cmd = string("");
    L_Fg_Cmd_Pid=PIDNULL;
    previousCd = NULL;
//	L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
//	if (L_Fg_Cmd == NULL)
//			exit (-1);
//	L_Fg_Cmd[0] = '\0';
	
    	while (1)
    	{
	 	printf("smash > ");
		fgets(lineSize, MAX_LINE_SIZE, stdin);
		strcpy(cmdString, lineSize);    	
		cmdString[strlen(lineSize)-1]='\0';
        history.addCommandToHistory(lineSize);
					// perform a complicated Command
		if(!ExeComp(lineSize)) continue; 
					// background command	
	 	if(!BgCmd(lineSize, jobsList)) continue;
					// built in commands
		ExeCmd(jobsList, lineSize, cmdString);
		
		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
    return 0;
}

