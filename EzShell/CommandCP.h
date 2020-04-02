#ifndef COMMANDCP_H
#define COMMANDCP_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandCP : public CommandBase {
public:
    CommandCP(string str);
    ~CommandCP();
};

#endif
