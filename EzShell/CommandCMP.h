#ifndef COMMANDCMP_H
#define COMMANDCMP_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandCMP : public CommandBase {
public:
    CommandCMP(string str);
    ~CommandCMP();
};

#endif
