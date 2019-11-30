//
//  ListOfJobs.cpp
//  AfalaRatouv1
//
//  Created by Nathan Benamou on 28/11/2019.
//  Copyright © 2019 Nathan Benamou. All rights reserved.
//

#include "ListOfJobs.h"

ListOfJobs::ListOfJobs()
{
    
}


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


int ListOfJobs::pidLastJob()
{
    if (_listJobs.size()) {
        return _listJobs.at(_listJobs.size()-1)._pid;
    }
    return PIDNULL;
}

int ListOfJobs::pidFromId(int id_io)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i).idJob == id_io){
            return _listJobs.at(i)._pid;
        }
    }
    return PIDNULL;
}


void ListOfJobs::printNameOfJob(int pid)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i)._pid == pid){
            cout << _listJobs.at(i)._jobName << endl;
        }
    }
}

void ListOfJobs::setJobStoppedFromPid(int pid, int newStatus)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i)._pid == pid){
            _listJobs.at(i).setJobStopped(newStatus);
        }
    }
}

int ListOfJobs::jobIsStopped(int pid)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i)._pid == pid){
            return _listJobs.at(i).isStopped();
        }
    }
    return FALSE;
}

int ListOfJobs::pidLastJobStopped()
{
    if(_listJobs.size() == 0){
        return PIDNULL;
    }
    
    for(unsigned long i = _listJobs.size()-1 ; i>=0 ; i--){
        if(_listJobs.at(i).isStopped()){
            return _listJobs.at(i)._pid;
        }
    }
    return PIDNULL;
}
