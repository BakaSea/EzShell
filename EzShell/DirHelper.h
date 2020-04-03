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
private:
    string path;
};

#endif