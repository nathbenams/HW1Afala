//
//  Jobs.hpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 25/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#ifndef Jobs_hpp
#define Jobs_hpp

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#define TRUE true
#define FALSE false
using namespace std;



class Jobs
{
    public :
    Jobs(string name,int pid);
    void jobsPrint();
    void setJobStopped(int newStatus);
    int isStopped();
    
    public:
    string _jobName;
    int _pid;
    time_t _startTime;
    static int nextId;
    int idJob;
    int finishJob;
    int jobStopped;
    
};

#endif /* Jobs_hpp */
