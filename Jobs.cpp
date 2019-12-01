//
//  Jobs.cpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 25/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//


#include "Jobs.h"

int Jobs::nextId = 0;

//********************************************
// function name: Constructor od Jobs
// Description: constructor
// Parameters: the name of the command and the pid
// Returns:NO
//**************************************************************************************
Jobs::Jobs(string name,pid_t pid){
    nextId++;
    _jobName = name;
    _pid = pid;
    _startTime = time(NULL);
    ctime(&_startTime);
    idJob = nextId;
    finishJob=FALSE;
    jobStopped=FALSE;
}
//********************************************
// function name: jobsPrint
// Description: print all the information of the job
// Parameters: no
// Returns:NO
//**************************************************************************************
void Jobs::jobsPrint()
{
    time_t timeCommand = time(NULL);
    if(timeCommand == -1){
        perror("time :");
        exit(-1);
    }
    cout << "[" << idJob << "] " << _jobName << " :" << _pid << " " << difftime(timeCommand, _startTime) << " secs" ;
    if (jobStopped){
        cout << " (Stopped)";
    }
    cout << endl;
}
//********************************************
// function name: setJobStopped
// Description: Set the indicator of Stopped
// Parameters: the new status
// Returns:NO
//**************************************************************************************
void Jobs::setJobStopped(int newStatus)
{
    jobStopped = newStatus;
}
//********************************************
// function name: isStopped
// Description: return if the job is stopped
// Parameters: no
// Returns: jobStopped
//**************************************************************************************
int Jobs::isStopped()
{
    return jobStopped;
}
