#ifndef COMMANDLS_H
#define COMMANDLS_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <string>
using namespace std;

class CommandLS : public CommandBase {
public:
    CommandLS(string str, DirHelper *dirHelper);
    ~CommandLS();
    void run();
private:
    void show(string str);
};

#endif