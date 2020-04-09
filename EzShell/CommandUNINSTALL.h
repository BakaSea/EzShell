#ifndef COMMANDUNINSTALL_H
#define COMMANDUNINSTALL_H
#include "CommandBase.h"
#include <unordered_map>
using namespace std;

class CommandUNINSTALL : public CommandBase {
public:
    CommandUNINSTALL(string str, DirHelper *dirHelper, unordered_map<string, bool> *mapCom);
    ~CommandUNINSTALL();
    void run();
private:
    unordered_map<string, bool> *mapCom;
};

#endif