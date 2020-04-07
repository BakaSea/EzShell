#include "CommandBase.h"

CommandBase::CommandBase(string name, string str, DirHelper *dirHelper) : name(name), strSrc(str), dirHelper(dirHelper), help("") {
    splitCommand();
}

CommandBase::~CommandBase() {
    command.clear();
    files.clear();
    opt.clear();
    mapOpt.clear();
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
    for (int i = 0; i < strSrc.size(); ++i) {
        if (strSrc[i] == ' ' || strSrc[i] == '\t' ) {
            if (flag) {
                flag = 0;
                command.push_back(s);
                s = string();
            }
            continue;
        } else {
            flag = 1;
            s.push_back(strSrc[i]);
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

int CommandBase::analyzeOpt() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i].size() > 1) {
            if (opt[i][0] == '-') {
                if (opt[i][1] == '-') {
                    unordered_map<string, bool*>::iterator iter = mapOpt.find(opt[i]);
                    if (iter != mapOpt.end()) {
                        (*iter->second) = true;
                    } else if (opt[i] == "--help") {
                        cout << help;
                        return 0;
                    } else {
                        cout << name << ": unrecognized option \'" << opt[i] << "\'" << endl;
                        cout << "Try \'" << name << " --help\' for more information" << endl;
                        return 0;
                    }
                } else {
                    for (int j = 1; j < opt[i].size(); ++j) {
                        unordered_map<string, bool*>::iterator iter = mapOpt.find(string(1, opt[i][j]));
                        if (iter != mapOpt.end()) {
                            (*iter->second) = true;
                        } else {
                            cout << name << ": unrecognized option \'" << opt[i][j] << "\'" << endl;
                            cout << "Try \'" << name << " --help\' for more information" << endl;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}