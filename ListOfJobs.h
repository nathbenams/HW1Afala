//
//  ListOfJobs.hpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 28/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#ifndef ListOfJobs_hpp
#define ListOfJobs_hpp

#define PIDNULL -1
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;

#include "Jobs.h"

class ListOfJobs
{
    public:
    ListOfJobs();
    void listJobsPrint();
    int pidLastJob();
    int pidLastJobStopped();
    int pidFromId(int id_io);
    void printNameOfJob(int pid);
    void setJobStoppedFromPid(int pid,int newStatus);
    int jobIsStopped(int pid);
    void removeJobFromPid(int pid);
    void addJobToList(int pid, string cmd);
    
    public :
    vector<Jobs> _listJobs;
};

#endif /* ListOfJobs_hpp */
