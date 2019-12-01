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

//********************************************
// function name: handler_cntlc
// Description: handle the signal send by CTRL+C
// Parameters: signum
// Returns:NO
//**************************************************************************************
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

//********************************************
// function name: pidLastJob
// Description: return the pid of the last job
// Parameters: NO
// Returns:The pid of the last job
//**************************************************************************************
int ListOfJobs::pidLastJob()
{
    if (_listJobs.size()) {
        return _listJobs.at(_listJobs.size()-1)._pid;
    }
    return PIDNULL;
}
//********************************************
// function name: pidFromId
// Description: return the pid of the job with the id entered by the user
// Parameters: id
// Returns:the pid if hes found, PIDNULL if not
//**************************************************************************************
int ListOfJobs::pidFromId(int id_io)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i).idJob == id_io){
            return _listJobs.at(i)._pid;
        }
    }
    return PIDNULL;
}
//********************************************
// function name: printNameOfJob
// Description: print the name of the job with the specific pid
// Parameters: pid
// Returns:no
//**************************************************************************************

void ListOfJobs::printNameOfJob(int pid)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i)._pid == pid){
            cout << _listJobs.at(i)._jobName << endl;
        }
    }
}
//********************************************
// function name: setJobStoppedFromPid
// Description: change the status "stopped" of the job with the specific id
// Parameters: pid and the newstatus of "stopped"
// Returns:NO
//**************************************************************************************
void ListOfJobs::setJobStoppedFromPid(int pid, int newStatus)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i)._pid == pid){
            _listJobs.at(i).setJobStopped(newStatus);
        }
    }
}
//********************************************
// function name: jobIsStopped
// Description: give the information if the job with the specific pid is stopped
// Parameters: pid
// Returns:1 - success,0 - failure
//**************************************************************************************
int ListOfJobs::jobIsStopped(int pid)
{
    for(int i = 0;i<_listJobs.size();i++){
        if(_listJobs.at(i)._pid == pid){
            return _listJobs.at(i).isStopped();
        }
    }
    return FALSE;
}
//********************************************
// function name: pidLastJobStopped
// Description: handle the signal send by CTRL+C
// Parameters: no
// Returns:pid of the last job stopped, PIDNULL if there is not
//**************************************************************************************
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
//********************************************
// function name: removeJobFromPid
// Description: remove the job with the pid from the parameter
// Parameters: pid
// Returns:NO
//**************************************************************************************
void ListOfJobs::removeJobFromPid(int pid)
{
    unsigned long i=0;
    while (i < _listJobs.size()) {
        if(_listJobs.at(i)._pid == pid){
            _listJobs.erase(_listJobs.begin()+i);
        }
        i++;
    }
}
//********************************************
// function name: addJobToList
// Description: add the job to the list
// Parameters: pid and name
// Returns:NO
//**************************************************************************************
void ListOfJobs::addJobToList(int pid, string cmd)
{
    _listJobs.push_back(Jobs(cmd, pid));
}
