#ifndef COMMANDCD_H
#define COMMANDCD_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <string>
#include <vector>
using namespace std;

class CommandCD : public CommandBase {
public:
    CommandCD(string str, DirHelper *dirHelper);
    ~CommandCD();
    void run();
private:
    vector<string> path;
    void splitPath(string str);
    bool checkPath(string str);
};

#endif