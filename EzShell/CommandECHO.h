#ifndef COMMANDECHO_H
#define COMMANDECHO_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandECHO : public CommandBase {
public:
    CommandECHO(string str, DirHelper *dirHelper);
    ~CommandECHO();
    void run();
};

#endif
