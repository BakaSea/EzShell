#include "Command.h"

Command::Command() {

}

Command::~Command() {
    delete command;
}

int Command::find(string str) {
    string s = string();
    for (int i = 0; i < str.size(); ++i) {
        if ((str[i] == ' ' || str[i] == '\t') && s.empty()) continue;
        if (str[i] != ' ' && str[i] != '\t') s.push_back(str[i]);
        else break;
    }
    command = NULL;
    if (s == "cp") command = new CommandCP(str);
    if (s == "cmp") command = new CommandCMP(str);
    if (s == "wc") command = new CommandWC(str);
    if (s == "cat") command = new CommandCAT(str);
    if (s == "man") command = new CommandMAN(str);
    if (s == "echo") command = new CommandECHO(str);
    if (s == "exit") return -1;
    if (s.empty()) return -2;
    return command != NULL;
}

void Command::run() {
    command->run();
}

