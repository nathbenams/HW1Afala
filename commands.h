#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "HistoryCommands.h"
#include "ListOfJobs.h"
#include "Jobs.h"
#include "signals.h"
#define MAX_LINE_SIZE 80
#define MAX_ARG 20
#define PIDNULL -1
#define MAXPWD 255
//typedef enum { FALSE , TRUE } bool;
#define TRUE true
#define FALSE false
int ExeComp(char* lineSize);
int BgCmd(char* lineSize, void* jobs);
int ExeCmd(void* jobs, char* lineSize, char* cmdString);
void ExeExternal(char *args[MAX_ARG], char* cmdString);

#endif

