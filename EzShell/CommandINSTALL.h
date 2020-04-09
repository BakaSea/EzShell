#ifndef COMMANDINSTALL_H
#define COMMANDINSTALL_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <unordered_map>
using namespace std;

class CommandINSTALL : public CommandBase {
public:
    CommandINSTALL(string str, DirHelper *dirHelper, unordered_map<string, bool> *mapCom);
    ~CommandINSTALL();
    void run();
private:
    unordered_map<string, bool> *mapCom;
};

#endif