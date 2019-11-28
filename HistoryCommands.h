//
//  HistoryCommands.h
//  
//
//  Created by Nathan Benamou on 28/11/2019.
//

#ifndef HistoryCommands_h
#define HistoryCommands_h
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#define MAX_COMMANDS 50

class HistoryCommands
{
public:
    HistoryCommands();
    void printHistory();
    void addCommandToHistory(char* command);
    
private:
    vector<string> _history;
};

#endif /* HistoryCommands_h */
