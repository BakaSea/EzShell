#include "Command.h"
#include "CommandCP.h"
#include "CommandCMP.h"
#include "CommandWC.h"
#include "CommandCAT.h"
#include "CommandMAN.h"
#include "CommandECHO.h"
#include "CommandBase.h"
#include "CommandLS.h"
#include "CommandPWD.h"
#include "CommandCD.h"
#include "CommandMKDIR.h"
#include "CommandTOUCH.h"
#include "CommandRM.h"
#include "CommandRMDIR.h"

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
    if (s == "ls") command = new CommandLS(str, dirHelper);
    if (s == "pwd") command = new CommandPWD(str, dirHelper);
    if (s == "cd") command = new CommandCD(str, dirHelper);
    if (s == "mkdir") command = new CommandMKDIR(str, dirHelper);
    if (s == "touch") command = new CommandTOUCH(str, dirHelper);
    if (s == "rm") command = new CommandRM(str, dirHelper);
    if (s == "rmdir") command = new CommandRMDIR(str, dirHelper);
    if (s == "exit") return -1;
    if (s.empty()) return -2;
    if (s.size() >= 2 && s[0] == '.' && s[1] == '/') return -3;
    return command != NULL;
}

void Command::run() {
    command->run();
}

