#ifndef DIRHELPER_H
#define DIRHELPER_H
#include <string>
using namespace std;

class DirHelper {
public:
    DirHelper();
    ~DirHelper();
    string getPath();
    string getFilePath(string str);
    string initPath();
    void setPath(string str);
    string back(string str);
    string backToUser();
    string getFinalDir(string str);
    int contain(string A, string B);
private:
    string path;
};

#endif