#ifndef COMMANDBASE_H
#define COMMANDBASE_H
#include <string>
#include <vector>
#include <iostream>
#include "DirHelper.h"
using namespace std;

class CommandBase {
public:
    CommandBase(string name, string str, DirHelper *dirHelper);
    ~CommandBase();
    virtual void run();
protected:
    string str, name;
    DirHelper *dirHelper;
    vector<string> command;
    vector<string> files;
    vector<string> opt;
    void splitCommand();
};

#endif
