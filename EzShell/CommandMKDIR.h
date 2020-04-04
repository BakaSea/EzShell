#ifndef COMMANDMKDIR_H
#define COMMANDMKDIR_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <string>
#include <vector>
using namespace std;

class CommandMKDIR : public CommandBase {
public:
    CommandMKDIR(string str, DirHelper *dirHelper);
    ~CommandMKDIR();
    void run();
};

#endif