#include "CommandMKDIR.h"
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include "CommandMAN.h"
using namespace std;

CommandMKDIR::CommandMKDIR(string str, DirHelper *dirHelper) : CommandBase("mkdir", str, dirHelper) {
    help =
"Usage: mkdir [OPTION]... DIRECTORY...\n\
Create the DIRECTORY(ies), if they do not already exist.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\
      --help     display this help and exit\n";
}

CommandMKDIR::~CommandMKDIR() {

}

void CommandMKDIR::run() {
    if (!analyzeOpt()) return;
    if (files.empty()) {
        cout << "mkdir: missing operand" << endl;
        cout << "Try \'mkdir --help\' for more information." << endl;
        return;
    }
    for (int i = 0; i < files.size(); ++i) {
        if (mkdir(dirHelper->getFilePath(files[i]).c_str(), 0755)) {
            cout << "mkdir: cannot create directory \'"+files[i]+"\'" << endl;
        }
    }
}