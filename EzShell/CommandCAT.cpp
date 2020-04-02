#include "CommandCAT.h"
#include <iostream>
#include <fstream>

CommandCAT::CommandCAT(string str) : CommandBase(str) {

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
    ifstream file(str);
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
        if (opt[i] == "-n") {
            _n = true;
        } else if (opt[i] == "-b") {
            _b = true;
        } else if (opt[i] == "-s") {
            _s = true;
        } else if (opt[i] == "-E") {
            _E = true;
        } else if (opt[i] == "--help") {

        } else {
            cout << "cat: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'cat --help\' for more information" << endl;
        }
    }
    for (int i = 0; i < files.size(); ++i) {
        display(files[i]);
    }
}
