#ifndef COMMANDBASE_H
#define COMMANDBASE_H
#include<string>
#include<vector>
#include<iostream>
using namespace std;

class CommandBase {
public:
    CommandBase(string str);
    ~CommandBase();
    virtual void run();
protected:
    string str;
    vector<string> command;
    vector<string> files;
    vector<string> opt;
    void splitCommand();
};

#endif
