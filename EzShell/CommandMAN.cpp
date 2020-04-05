#include "CommandMAN.h"
#include <fstream>
#include <iostream>

CommandMAN::CommandMAN(string str, DirHelper *dirHelper) : CommandBase("man", str, dirHelper) {

}

CommandMAN::~CommandMAN() {

}

void CommandMAN::show(string str) {
    ifstream in(dirHelper->getPath()+"/help/"+str);
    if (in) {
        string s;
        while (getline(in, s)) {
            cout << s << endl;
        }
        in.close();
    } else cout << "No manual entry for " << str << endl;
}

void CommandMAN::run() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i].size() > 1) {
            if (opt[i][0] == '-') {
                if (opt[i][1] == '-') {
                    if (opt[i] == "--help") {
                        show("man");
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
    if (files.empty()) cout << "What manual page do you want?" << endl;
    else show(files[0]);
}