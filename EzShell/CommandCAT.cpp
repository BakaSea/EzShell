#include "CommandCAT.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "CommandMAN.h"
using namespace std;

CommandCAT::CommandCAT(string str, DirHelper *dirHelper) : CommandBase("cat", str, dirHelper) {

}

CommandCAT::~CommandCAT() {

}

bool CommandCAT::checkBlank(string str) {
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ' && str[i] != '\t') return 0;
    }
    return 1;
}

void CommandCAT::display(string str) {
    struct stat path;
    stat((dirHelper->getPath()+"/"+str).c_str(), &path);
    if (S_ISDIR(path.st_mode)) {
        cout << "cat: " << str << ": Is a directory" << endl;
        return;
    } 
    ifstream file(dirHelper->getPath()+"/"+str);
    if (file) {
        string s = string();
        int curBlank = 0, preBlank = 0, num = 0;
        while (getline(file, s)) {
            curBlank = checkBlank(s);
            if (_s && curBlank && preBlank) continue;
            if (_b && !curBlank) cout << ++num << ' ';
            else if (_n) cout << ++num << ' ';
            cout << s;
            if (_E) cout << "$";
            cout << endl;
            preBlank = curBlank;
        }
        file.close();
    } else cout << "cat: " << str << ": No such file or directory" << endl;
}

void CommandCAT::run() {
    _n = _b = _s = _E = false;
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
                        if (opt[i][j] == 'n') {
                            _n = true;
                        } else if (opt[i][j] == 'b') {
                            _b = true;
                        } else if (opt[i][j] == 's') {
                            _s = true;
                        } else if (opt[i][j] == 'E') {
                            _E = true;
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
    for (int i = 0; i < files.size(); ++i) {
        display(files[i]);
    }
}
