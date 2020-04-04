#include "CommandBase.h"

CommandBase::CommandBase(string str, DirHelper *dirHelper) : str(str), dirHelper(dirHelper) {
    splitCommand();
}

CommandBase::~CommandBase() {
    command.clear();
    files.clear();
    opt.clear();
    dirHelper = NULL;
    delete dirHelper;
}

void CommandBase::run() {
    for (int i = 0; i < command.size(); ++i) {
        cout << command[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < files.size(); ++i) {
        cout << files[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < opt.size(); ++i) {
        cout << opt[i] << ' ';
    }
    cout << endl;
}

void CommandBase::splitCommand() {
    command.clear();
    files.clear();
    opt.clear();
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
    vector<string> originFile;
    originFile.clear();
    for (int i = 1; i < command.size(); ++i) {
        if (command[i][0] == '-') {
            opt.push_back(command[i]);
        } else {
            originFile.push_back(command[i]);
        }
    }
    if (originFile.size()) {
        files.push_back(originFile[0]);
        for (int i = 1, j = 0; i < originFile.size(); ++i) {
            if (files[j][files[j].size()-1] == '\\') {
                files[j].pop_back();
                files[j] += " "+originFile[i];
            } else {
                files.push_back(originFile[i]);
                j++;
            }
        }
    }
}
