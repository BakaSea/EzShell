#ifndef COMMAND_H
#define COMMAND_H
#include "CommandCP.h"
#include "CommandCMP.h"
#include "CommandWC.h"
#include "CommandCAT.h"
#include "CommandMAN.h"
#include "CommandBase.h"
#include <string>
using namespace std;

class Command {
public:
    Command();
    ~Command();
    int find(string str);
    void run();
private:
    CommandBase *command;
};

#endif
