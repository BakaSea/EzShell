#ifndef COMMANDRMDIR_H
#define COMMANDRMDIR_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <vector>
#include <string>
using namespace std;

class CommandRMDIR : public CommandBase {
public:
    CommandRMDIR(string str, DirHelper *dirHelper);
    ~CommandRMDIR();
    void run();
private:
    bool _p;
    vector<string> path;
    void splitPath(string str);
};

#endif