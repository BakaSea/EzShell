#ifndef COMMAND_H
#define COMMAND_H
#include "DirHelper.h"
#include "CommandBase.h"
#include <string>
using namespace std;

class Command {
public:
    Command(DirHelper *dirHelper);
    ~Command();
    int find(string str);
    void run();
private:
    CommandBase *command;
    DirHelper *dirHelper;
};

#endif
