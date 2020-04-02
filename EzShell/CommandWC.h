#ifndef COMMANDWC_H
#define COMMANDWC_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandWC : public CommandBase {
public:
    CommandWC(string str);
    ~CommandWC();
};

#endif
