#ifndef COMMANDCP_H
#define COMMANDCP_H
#include "CommandBase.h"
#include <string>
#include <vector>
using namespace std;

class CommandCP : public CommandBase {
public:
    CommandCP(string str, DirHelper *dirHelper);
    ~CommandCP();
    void run();
private:
    bool _r, _i;
    void copy(string src, string dest, string direct);
    void copyFile(string src, string dest);
    void copyDir(string src, string direct);
};

#endif
