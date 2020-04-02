#include "CommandBase.h"
#include <iostream>

CommandBase::CommandBase(string str) : str(str) {
    splitCommand();
}

CommandBase::~CommandBase() {
    command.clear();
}

void CommandBase::run() {
    for (int i = 0; i < command.size(); ++i) {
        cout << command[i] << ' ';
    }
    cout << endl;
}

void CommandBase::splitCommand() {
    string s = string();
    int flag = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ' ' || str[i] == '\t' ) {
            if (flag) {
                flag = 0;
                command.push_back(s);
                s = string();
            }
            continue;
        } else {
            flag = 1;
            s.push_back(str[i]);
        }
    }
    if (!s.empty()) command.push_back(s);
}
