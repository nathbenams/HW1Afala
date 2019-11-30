#ifndef _SIGS_H
#define _SIGS_H
#define TRUE true
#define FALSE false
#define PIDNULL -1
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string>

using namespace std;
#include "Jobs.h"
#include "ListOfJobs.h"


bool setSignalHandler();
void handler_cntlc(int signum);
void handler_cntlz(int signum);
bool sendSignal(int pid , int sig , const char* sigName);
#endif

