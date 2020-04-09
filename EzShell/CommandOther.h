#ifndef COMMANDOTHER_H
#define COMMANDOTHER_H
#include "CommandBase.h"
#include "DirHelper.h"

class CommandOther : public CommandBase {
public:
    CommandOther(string str, DirHelper *dirHelper, string path);
    ~CommandOther();
    void run();
private:
    string path;
};

#endif