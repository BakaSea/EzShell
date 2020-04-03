#include "CommandMKDIR.h"
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

CommandMKDIR::CommandMKDIR(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

}

CommandMKDIR::~CommandMKDIR() {

}

void CommandMKDIR::run() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "--help") {

        } else {
            cout << "mkdir: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'mkdir --help\' for more information" << endl;
            return;
        }
    }
    if (files.empty()) {
        cout << "mkdir: missing operand" << endl;
        cout << "Try \'mkdir --help\' for more information." << endl;
        return;
    }
    mk.clear();
    mk.push_back(1);
    for (int i = 0, j = 1; j < files.size(); ++j) {
        if (files[i][files[i].size()-1] == '\\') {
            files[i].pop_back();
            files[i] += " "+files[j];
            mk.push_back(0);
        } else {
            i = j;
            mk.push_back(1);
        }
    }
    for (int i = 0; i < files.size(); ++i) {
        if (mk[i]) {
            if (mkdir(files[i].c_str(), 0755)) {
                cout << "mkdir: cannot create directory \'"+files[i]+"\': No such file or directory" << endl;
            }
        }
    }
}