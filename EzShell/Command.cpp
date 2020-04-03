#include "Command.h"

Command::Command(DirHelper *dirHelper) : dirHelper(dirHelper) {

}

Command::~Command() {
    dirHelper = NULL;
    delete dirHelper;
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
    if (s == "cp") command = new CommandCP(str, dirHelper);
    if (s == "cmp") command = new CommandCMP(str, dirHelper);
    if (s == "wc") command = new CommandWC(str, dirHelper);
    if (s == "cat") command = new CommandCAT(str, dirHelper);
    if (s == "man") command = new CommandMAN(str, dirHelper);
    if (s == "echo") command = new CommandECHO(str, dirHelper);
    if (s == "exit") return -1;
    if (s.empty()) return -2;
    return command != NULL;
}

void Command::run() {
    command->run();
}

