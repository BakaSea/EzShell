#include "DirHelper.h"
#include <unistd.h>
#include <pwd.h>

DirHelper::DirHelper() {

}

DirHelper::~DirHelper() {

}

string DirHelper::getPath() {
    return path;
}

string DirHelper::initPath() {
    char cwd[257];
    getcwd(cwd, 257);
    return string(cwd);
}

void DirHelper::setPath(string str) {
    path = str;
}

string DirHelper::back(string str) {
    string s = str;
    while (s[s.size()-1] != '/') {
        s.pop_back();
    }
    if (s.size() > 1) s.pop_back();
    return s;
}

string DirHelper::backToUser() {
    string s = getpwuid(getuid())->pw_name;
    if (s == "root") return "/root";
    else return "/home/"+s;
}