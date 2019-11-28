//
//  ListOfJobs.hpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 28/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#ifndef ListOfJobs_hpp
#define ListOfJobs_hpp

#include <stdio.h>
using namespace std;
#include "signals.h"
#include <iostream>
#include <vector>
#include "Jobs.h"
#include <stdlib.h>

class ListOfJobs
{
    public:
    ListOfJobs();
    
    public :
    vector<Jobs> _listJobs;
};

#endif /* ListOfJobs_hpp */
