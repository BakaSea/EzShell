#ifndef COMMANDTOUCH_H
#define COMMANDTOUCH_H
#include "CommandBase.h"
#include "DirHelper.h"

class CommandTouch : public CommandBase {
public:
    CommandTouch(string str, DirHelper *dirHelper);
    ~CommandTouch();
    void run();
};

#endif