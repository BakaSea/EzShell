#include "DirHelper.h"
#include <unistd.h>
#include <pwd.h>
#include <vector>
using namespace std;

DirHelper::DirHelper() {

}

DirHelper::~DirHelper() {

}

string DirHelper::getPath() {
    return path;
}

string DirHelper::getFilePath(string str) {
    if (str.empty()) return "";
    return str[0] == '/' ? str : getPath()+"/"+str;
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

string DirHelper::getFinalDir(string str) {
    string dir = "";
    for (int i = str.size()-1, flag = 0; i >= 0; --i) {
        if (str[i] != '/') flag = 1;
        if (str[i] == '/' && flag) {
            for (int j = i+1; j < str.size(); ++j) {
                dir.push_back(str[j]);
            }
            break;
        }
    }
    if (dir.empty()) dir = str;
    return dir;
}

int DirHelper::contain(string A, string B) {
    vector<string> pathA, pathB;
    pathA.clear();
    pathB.clear();
    string s = "";
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] == '/') {
            if (s.empty()) pathA.push_back(".");
            else pathA.push_back(s);
            s.clear();
        } else {
            s.push_back(A[i]);
        }
    }
    if (s.size()) pathA.push_back(s);
    s.clear();
    for (int i = 0; i < B.size(); ++i) {
        if (A[i] == '/') {
            if (s.empty()) pathB.push_back(".");
            else pathB.push_back(s);
            s.clear();
        } else {
            s.push_back(B[i]);
        }
    }
    if (s.size()) pathB.push_back(s);
    string sa = "", sb = "";
    for (int i = 0; i < pathA.size(); ++i) {
        if (pathA[i] == "~") sa = backToUser();
        else if (pathA[i] == ".") continue;
        else if (pathA[i] == "..") sa = back(sa);
        else sa += "/"+pathA[i];
    }
    for (int i = 0; i < pathB.size(); ++i) {
        if (pathB[i] == "~") sb = backToUser();
        else if (pathB[i] == ".") continue;
        else if (pathB[i] == "..") sb = back(sb);
        else sb += "/"+pathB[i];
    }
    if (sa.size() >= sb.size()) return 0;
    for (int i = 0; i < sa.size(); ++i) {
        if (sa[i] != sb[i]) return 0;
    }
    return 1;
}