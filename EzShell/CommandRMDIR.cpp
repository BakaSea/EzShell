#include "CommandRMDIR.h"
#include "CommandMAN.h"
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

CommandRMDIR::CommandRMDIR(string str, DirHelper *dirHelper) : CommandBase("rmdir", str, dirHelper) {

}

CommandRMDIR::~CommandRMDIR() {

}

void CommandRMDIR::splitPath(string str) {
    path.clear();
    string s = string();
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '/') {
            if (s.empty()) path.push_back(".");
            else path.push_back(s);
            s.clear();
        } else {
            s.push_back(str[i]);
        }
    }
    if (s.size()) path.push_back(s);
}

void CommandRMDIR::run() {
    _p = false;
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
                        if (opt[i][j] == 'p') {
                            _p = true;
                        } else {
                            cout << name << ": unrecognized option \'" << opt[i][j] << "\'" << endl;
                            cout << "Try \'" << name << " --help\' for more information" << endl;
                            return;
                        }
                    }
                }
            }
        }
    }
    if (files.empty()) {
        cout << "rmdir: missing operand" << endl;
        cout << "Try \'rmdir --help\' for more information." << endl;
    } else for (int i = 0; i < files.size(); ++i) {
        struct stat cur;
        stat((dirHelper->getPath()+"/"+files[i]).c_str(), &cur);
        if (S_ISDIR(cur.st_mode)) {
            if (_p) {
                splitPath(files[i]);
                for (int j = path.size()-1; j >= 0; --j) {
                    string cur = string();
                    for (int k = 0; k <= j; ++k) {
                        cur += "/"+path[k];
                    }
                    if (rmdir((dirHelper->getPath()+"/"+cur).c_str())) {
                        cout << "rmdir: failed to remove \'" << cur << "\'" << endl;
                        break;
                    }
                }
            } else {
                if (rmdir((dirHelper->getPath()+"/"+files[i]).c_str())) {
                    cout << "rmdir: failed to remove \'" << files[i] << "\'" << endl;
                }
            }    
        } else {
            cout << "rmdir: failed to remove \'" << files[i] << "\'" << endl;
        }
    }
}