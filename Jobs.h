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
#include "Jobs.h"
#include "signals.h"

class Jobs
{
    public :
    Jobs(string name,int pid);
    
    public:
    string _jobName;
    int _pid;
    time_t _startTime;
    static int nextId;
    int idJob;
    
};

#endif /* Jobs_hpp */
