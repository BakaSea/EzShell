#include "CommandCAT.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "CommandMAN.h"
using namespace std;

CommandCAT::CommandCAT(string str, DirHelper *dirHelper) : CommandBase("cat", str, dirHelper) {
    mapOpt["b"] = &_b;
    mapOpt["--number-nonblank"] = &_b;
    mapOpt["E"] = &_E;
    mapOpt["--show-ends"] = &_E;
    mapOpt["n"] = &_n;
    mapOpt["--number"] = &_n;
    mapOpt["s"] = &_s;
    mapOpt["--squeeze-blank"] = &_s;
    help = 
"Usage: cat [OPTION]... [FILE]...\n\
Concatenate FILE(s) to standard output.\n\n\
  -b, --number-nonblank    number nonempty output lines, overrides -n\n\
  -E, --show-ends          display $ at end of each line\n\
  -n, --number             number all output lines\n\
  -s, --squeeze-blank      suppress repeated empty output lines\n\
      --help     display this help and exit\n";
}

CommandCAT::~CommandCAT() {

}

bool CommandCAT::checkBlank(string str) {
    if (str.empty()) return 1;
    return 0;
}

void CommandCAT::display(string str) {
    struct stat path;
    stat(dirHelper->getFilePath(str).c_str(), &path);
    if (S_ISDIR(path.st_mode)) {
        cout << "cat: \'" << str << "\': Is a directory" << endl;
        return;
    }
    ifstream file(dirHelper->getFilePath(str));
    if (file) {
        string s = string();
        int curBlank = 0, preBlank = 0, num = 0;
        while (getline(file, s)) {
            curBlank = checkBlank(s);
            if (_s && curBlank && preBlank) continue;
            if (_b) {
                if (!curBlank) cout << ++num << ' ';
            } else if (_n) cout << ++num << ' ';
            cout << s;
            if (_E) cout << "$";
            cout << endl;
            preBlank = curBlank;
        }
        file.close();
    } else cout << "cat: \'" << str << "\': " << strerror(errno) << endl;
}

void CommandCAT::run() {
    _n = _b = _s = _E = false;
    if (!analyzeOpt()) return;
    for (int i = 0; i < files.size(); ++i) {
        display(files[i]);
    }
}
