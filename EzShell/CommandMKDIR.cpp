#include "CommandMKDIR.h"
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include "CommandMAN.h"
using namespace std;

CommandMKDIR::CommandMKDIR(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

}

CommandMKDIR::~CommandMKDIR() {

}

void CommandMKDIR::run() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "--help") {
            CommandMAN *man = new CommandMAN("man mkdir", dirHelper);
            man->run();
            return;
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
    for (int i = 0; i < files.size(); ++i) {
        if (mkdir(files[i].c_str(), 0755)) {
            cout << "mkdir: cannot create directory \'"+files[i]+"\': No such file or directory" << endl;
        }
    }
}