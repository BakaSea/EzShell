#include "CommandMAN.h"
#include <fstream>
#include <iostream>

CommandMAN::CommandMAN(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

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
        if (opt[i] == "--help") {
            show("man");
            return;
        } else {
            cout << "man: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'man --help\' for more information" << endl;
            return;
        }
    }
    if (files.empty()) cout << "What manual page do you want?" << endl;
    else show(files[0]);
}