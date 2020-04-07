#ifndef COMMANDRM_H
#define COMMANDRM_H
#include "CommandBase.h"
#include "DirHelper.h"

class CommandRM : public CommandBase {
public:
    CommandRM(string str, DirHelper *dirHelper);
    ~CommandRM();
    void run();
private:
    bool _i, _r;
    int removeFile(string str);
    int removeDir(string str);
};

#endif