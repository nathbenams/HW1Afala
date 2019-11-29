// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
   Synopsis: handle the Control-C */
#include "signals.h"
extern string L_Fg_Cmd;

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
    if(sigaction(SIGINT,&siga_cntlc,NULL) || sigaction(SIGSTP, &siga_cntlz,NULL)){
        return FALSE;
    }
    return TRUE;
}

void handler_cntlc(int signum)
{
    
}

void handler_cntlz(int signum)
{
    
}
