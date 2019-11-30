//
//  HistoryCommands.cpp
//  
//
//  Created by Nathan Benamou on 28/11/2019.
//

#include "HistoryCommands.h"


HistoryCommands::HistoryCommands()
{
    
}
//**************************************************************************************
// function name: printHistory
// Description: Print the content of History
// Parameters: Nothing
// Returns: nothing
//**************************************************************************************
void HistoryCommands::printHistory(){
    for(int i=0;i<(int)_history.size();i++){
        cout << _history.at(i) ;
    }
}

//**************************************************************************************
// function name: addCommandToHistory
// Description: Add a command to the history if it's full erase the oldest one
// Parameters: command of the user
// Returns: nothing
//**************************************************************************************
void HistoryCommands::addCommandToHistory(char* command){
    if(_history.size() == MAX_COMMANDS){
        _history.erase(_history.begin());
    }
    _history.push_back(string(command));
}

