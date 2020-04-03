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
    bool _r, _f, _i;
    vector<string> cpFile;
    vector<bool> mk;
    void copy(string res, string dest, string direct);
    void copyFile(string res, string dest);
    void copyDir(string res, string direct);
};

#endif
