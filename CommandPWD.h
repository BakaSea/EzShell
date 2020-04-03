#ifndef COMMANDPWD_H
#define COMMANDPWD_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <string>
using namespace std;

class CommandPWD : public CommandBase {
public:
    CommandPWD(string str, DirHelper *dirHelper);
    ~CommandPWD();
    void run();
};

#endif