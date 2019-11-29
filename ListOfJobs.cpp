//
//  ListOfJobs.cpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 28/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "ListOfJobs.h"

void ListOfJobs::listJobsPrint()
{
    if(_listJobs.size() == 0){
        return;
    }
    int status;
    pid_t resultWait;
    for(int i =0;i<_listJobs.size()+1;i++){
        resultWait = waitpid(_listJobs.at(i)._pid,&status, WNOHANG);
        if (resultWait == -1) {
            perror("");
            exit(1);
        }
        else if(resultWait==-1){
            continue;
        }
        else{
            //remove job
            i--;
        }
    }
    for(int i =0;i < _listJobs.size();i++){
        _listJobs.at(i).jobsPrint();
    }
}
