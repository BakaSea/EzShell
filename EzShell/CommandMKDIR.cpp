#include "CommandMKDIR.h"
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include "CommandMAN.h"
using namespace std;

CommandMKDIR::CommandMKDIR(string str, DirHelper *dirHelper) : CommandBase("mkdir", str, dirHelper) {

}

CommandMKDIR::~CommandMKDIR() {

}

void CommandMKDIR::run() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i].size() > 1) {
            if (opt[i][0] == '-') {
                if (opt[i][1] == '-') {
                    if (opt[i] == "--help") {
                        CommandMAN *man = new CommandMAN("man "+name, dirHelper);
                        man->run();
                        return;
                    } else {
                        cout << name << ": unrecognized option \'" << opt[i] << "\'" << endl;
                        cout << "Try \'" << name << " --help\' for more information" << endl;
                        return;
                    }
                } else {
                    for (int j = 1; j < opt[i].size(); ++j) {
                        cout << name << ": unrecognized option \'" << opt[i][j] << "\'" << endl;
                        cout << "Try \'" << name << " --help\' for more information" << endl;
                        return;
                    }
                }
            }
        }
    }
    if (files.empty()) {
        cout << "mkdir: missing operand" << endl;
        cout << "Try \'mkdir --help\' for more information." << endl;
        return;
    }
    for (int i = 0; i < files.size(); ++i) {
        if (mkdir(files[i].c_str(), 0755)) {
            cout << "mkdir: cannot create directory \'"+files[i]+"\'" << endl;
        }
    }
}