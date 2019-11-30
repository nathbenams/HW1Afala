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

bool sendSignal(int pid , int sig , const char* sigName)
{
    printf("signal %s was sent to pid %d\n", sigName,pid);
    
    if(kill(pid, sig)==-1){
        perror("");
        return FALSE;
        
    }
    return TRUE;
}
