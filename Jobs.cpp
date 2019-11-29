//
//  Jobs.cpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 25/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//


#include "Jobs.h"

int Jobs::nextId = 0;


Jobs::Jobs(string name,pid_t pid){
    nextId++;
    _jobName = name;
    _pid = pid;
    _startTime = time(NULL);
    ctime(&_startTime);
    idJob = nextId;
    finishJob=0;
    jobStopped=0;
}

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
