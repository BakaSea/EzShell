#include "CommandMAN.h"
#include <fstream>
#include <iostream>

CommandMAN::CommandMAN(string str, DirHelper *dirHelper) : CommandBase("man", str, dirHelper) {
    help = "Usage: man PAGE\n";
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
    if (!analyzeOpt()) return;
    if (files.empty()) cout << "What manual page do you want?" << endl;
    else show(files[0]);
}