#ifndef COMMANDMAN_H
#define COMMANDMAN_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandMAN : public CommandBase {
public:
    CommandMAN(string str, DirHelper *dirHelper);
    ~CommandMAN();
};

#endif
