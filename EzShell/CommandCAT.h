#ifndef COMMANDCAT_H
#define COMMANDCAT_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandCAT : public CommandBase {
public:
    CommandCAT(string str, DirHelper *dirHelper);
    ~CommandCAT();
    void run();
private:
    bool _n, _b, _s, _E;
    void display(string str);
    bool checkBlank(string str);
};

#endif
