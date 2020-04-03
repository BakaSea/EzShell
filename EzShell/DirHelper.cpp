#include "DirHelper.h"
#include <unistd.h>

DirHelper::DirHelper() {

}

DirHelper::~DirHelper() {

}

string DirHelper::getPath() {
    return path;
}

void DirHelper::initPath() {
    char cwd[257];
    getcwd(cwd, 257);
    path = cwd;
}