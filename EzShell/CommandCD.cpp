#include "CommandCD.h"
#include <iostream>
#include <dirent.h>
#include "CommandMAN.h"

CommandCD::CommandCD(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

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
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "--help") {
            CommandMAN *man = new CommandMAN("man cd", dirHelper);
            man->run();
            return;
        } else {
            cout << "cd: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'cd --help\' for more information" << endl;
            return;
        }
    }
    if (files.empty()) files.push_back("~");
    for (int i = 1; i < files.size(); ++i) {
        if (files[0][files[0].size()-1] == '\\') {
            files[0].pop_back();
            files[0] += " "+files[i];
        } else break;
    }
    splitPath(files[0]);
    string cur = dirHelper->getPath();
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
            cur += "/"+path[i];
            if (!checkPath(cur)) {
                cout << "cd: can't cd to " << cur << endl;
                flag = false;
                break;
            }
        }
    }
    if (flag) dirHelper->setPath(cur);
}