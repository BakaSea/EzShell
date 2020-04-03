#ifndef WORKSHELL_H
#define WORKSHELL_H
#include "DirHelper.h"
#include <string>
using namespace std;

class WorkShell {
public:
    WorkShell(string str, DirHelper *dirHelper);
    ~WorkShell();
    void run();
private:
    DirHelper *dirHelper;
    string str, fileName;
};

#endif