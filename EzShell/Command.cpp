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
#include "CommandOther.h"
#include "CommandINSTALL.h"
#include "CommandUNINSTALL.h"
#include <fstream>
using namespace std;

Command::Command(DirHelper *dirHelper) : dirHelper(dirHelper) {
    mapCom.clear();
    ifstream in("addons/config.txt");
    if (in) {
        string s;
        while (in >> s) {
            if (s.empty()) break;
            mapCom[s] = true;
        }
        in.close();
    }
    mapCom["cp"] = mapCom["cmp"] = mapCom["wc"] = mapCom["cat"] = mapCom["man"] = mapCom["echo"] = mapCom["ls"] = mapCom["exit"] =
        mapCom["pwd"] = mapCom["cd"] = mapCom["mkdir"] = mapCom["touch"] = mapCom["rm"] = mapCom["rmdir"] = mapCom["install"] =
        mapCom["uninstall"] = false;
}

Command::~Command() {
    mapCom.clear();
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
    unordered_map<string, bool>::iterator iter = mapCom.find(s);
    if (s == "cp") command = new CommandCP(str, dirHelper);
    else if (s == "cmp") command = new CommandCMP(str, dirHelper);
    else if (s == "wc") command = new CommandWC(str, dirHelper);
    else if (s == "cat") command = new CommandCAT(str, dirHelper);
    else if (s == "man") command = new CommandMAN(str, dirHelper);
    else if (s == "echo") command = new CommandECHO(str, dirHelper);
    else if (s == "ls") command = new CommandLS(str, dirHelper);
    else if (s == "pwd") command = new CommandPWD(str, dirHelper);
    else if (s == "cd") command = new CommandCD(str, dirHelper);
    else if (s == "mkdir") command = new CommandMKDIR(str, dirHelper);
    else if (s == "touch") command = new CommandTOUCH(str, dirHelper);
    else if (s == "rm") command = new CommandRM(str, dirHelper);
    else if (s == "rmdir") command = new CommandRMDIR(str, dirHelper);
    else if (s == "install") command = new CommandINSTALL(str, dirHelper, &mapCom);
    else if (s == "uninstall") command = new CommandUNINSTALL(str, dirHelper, &mapCom);
    else if (s == "exit") return -1;
    else if (iter != mapCom.end()) command = new CommandOther(str, dirHelper, "addons/"+s);
    else if (s.empty()) return -2;
    else if (s.size() >= 2 && s[0] == '.' && s[1] == '/') return -3;
    return command != NULL;
}

void Command::run() {
    command->run();
}

