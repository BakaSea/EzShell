#ifndef DIRHELPER_H
#define DIRHELPER_H
#include <string>
using namespace std;

class DirHelper {
public:
    DirHelper();
    ~DirHelper();
    string getPath();
    void initPath();
    void setPath(string str);
    string back(string str);
    string backToUser();
private:
    string path;
};

#endif