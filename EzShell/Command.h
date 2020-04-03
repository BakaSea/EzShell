#ifndef COMMAND_H
#define COMMAND_H
#include "CommandCP.h"
#include "CommandCMP.h"
#include "CommandWC.h"
#include "CommandCAT.h"
#include "CommandMAN.h"
#include "CommandECHO.h"
#include "CommandBase.h"
#include "DirHelper.h"
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
