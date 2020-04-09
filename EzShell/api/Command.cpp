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
    //TODO
    return command != NULL;
}

void Command::run() {
    command->run();
}

