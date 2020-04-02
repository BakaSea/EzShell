#ifndef COMMANDCAT_H
#define COMMANDCAT_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandCAT : public CommandBase {
public:
    CommandCAT(string str);
    ~CommandCAT();
};

#endif
