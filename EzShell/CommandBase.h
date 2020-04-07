#ifndef COMMANDBASE_H
#define COMMANDBASE_H
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "DirHelper.h"
using namespace std;

class CommandBase {
public:
    CommandBase(string name, string str, DirHelper *dirHelper);
    ~CommandBase();
    virtual void run();
protected:
    string strSrc, name, help;
    DirHelper *dirHelper;
    vector<string> command;
    vector<string> files;
    vector<string> opt;
    unordered_map<string, bool*> mapOpt;
    void splitCommand();
    int analyzeOpt();
};

#endif
