//
//  Jobs.cpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 25/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "Jobs.h"
#include "signals.h"
#include <stdio.h>
#include <time.h>
int Jobs::nextId = 0;


Jobs::Jobs(string name,pid_t pid){
    nextId++;
    _jobName = name;
    _pid = pid;
    _startTime = time(NULL);
    ctime(&_startTime);
    idJob = nextId;
}
