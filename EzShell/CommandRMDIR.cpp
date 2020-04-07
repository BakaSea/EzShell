#include "CommandRMDIR.h"
#include "CommandMAN.h"
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

CommandRMDIR::CommandRMDIR(string str, DirHelper *dirHelper) : CommandBase("rmdir", str, dirHelper) {
    mapOpt["p"] = &_p;
    mapOpt["--parents"] = &_p;
    help =
"Usage: rmdir [OPTION]... DIRECTORY...\n\
Remove the DIRECTORY(ies), if they are empty.\n\n\
  -p, --parents   remove DIRECTORY and its ancestors; e.g., 'rmdir -p a/b/c' is\n\
                    similar to 'rmdir a/b/c a/b a'\n\
      --help     display this help and exit\n";
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
    if (!analyzeOpt()) return;
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
                    string s = string();
                    for (int k = 0; k <= j; ++k) {
                        s += "/"+path[k];
                    }
                    if (rmdir((dirHelper->getPath()+s).c_str())) {
                        cout << "rmdir: failed to remove \'";
                        for (int k = 1; k < s.size(); ++k) cout << s[k];
                        cout << "\'" << endl;
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