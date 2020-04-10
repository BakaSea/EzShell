#include "CommandCD.h"
#include <iostream>
#include <dirent.h>
#include "CommandMAN.h"

CommandCD::CommandCD(string str, DirHelper *dirHelper) : CommandBase("cd", str, dirHelper) {
    help = 
"cd: cd [dir]\n\
    Change the shell working directory.\n\n\
    Change the current directory to DIR.  The default DIR is the value of the\n\
    HOME shell variable.\n";
}

CommandCD::~CommandCD() {

}

void CommandCD::splitPath(string str) {
    path.clear();
    string s = string();
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '/') {
            if (s.empty()) path.push_back(".");
            else path.push_back(s);
            s.clear();
        } else {
            s.push_back(str[i]);
        }
    }
    if (s.size()) path.push_back(s);
}

bool CommandCD::checkPath(string str) {
    DIR *dir = opendir(str.c_str());
    if (dir != NULL) {
        closedir(dir);
        return true;
    } else return false;
}

void CommandCD::run() {
    if (!analyzeOpt()) return;
    if (files.empty()) files.push_back("~");
    splitPath(files[0]);
    string cur = files[0][0] == '/' ? "/" : dirHelper->getPath();
    bool flag = true;
    for (int i = 0; i < path.size(); ++i) {
        if (path[i] == "~") {
            cur = dirHelper->backToUser();
            if (!checkPath(cur)) {
                cout << "cd: can't cd to " << cur << endl;
                flag = false;
                break;
            }
        } else if (path[i] == ".") {
            continue;
        } else if (path[i] == "..") {
            cur = dirHelper->back(cur);
            if (!checkPath(cur)) {
                cout << "cd: can't cd to " << cur << endl;
                flag = false;
                break;
            }
        } else {
            if (cur != "/") cur += "/"+path[i];
            else cur += path[i];
            if (!checkPath(cur)) {
                cout << "cd: can't cd to " << cur << endl;
                flag = false;
                break;
            }
        }
    }
    if (flag) dirHelper->setPath(cur);
}