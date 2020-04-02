#ifndef COMMANDBASE_H
#define COMMANDBASE_H
#include<string>
#include<vector>
using namespace std;

class CommandBase {
public:
    CommandBase(string str);
    ~CommandBase();
    void run();
protected:
    string str;
    vector<string> command;
    void splitCommand();
};

#endif
