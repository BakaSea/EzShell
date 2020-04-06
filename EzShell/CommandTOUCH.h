#ifndef COMMANDTOUCH_H
#define COMMANDTOUCH_H
#include "CommandBase.h"
#include "DirHelper.h"

class CommandTOUCH : public CommandBase {
public:
    CommandTOUCH(string str, DirHelper *dirHelper);
    ~CommandTOUCH();
    void run();
};

#endif