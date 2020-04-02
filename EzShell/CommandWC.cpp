#include "CommandWC.h"
#include <iostream>
#include <fstream>

CommandWC::CommandWC(string str) : CommandBase(str) {
    contents.clear();
}

CommandWC::~CommandWC() {
    contents.clear();
}

void CommandWC::count(Content &A) {
    ifstream file(A.file, ios::in);
    if (file) {
        file.seekg(0, ios::end);
        A.bytes = file.tellg();
        file.seekg(0, ios::beg);
        char ch;
        int length = 0, flag = 0;
        while (file.get(ch)) {
            A.chars++;
            if (ch == '\n') {
                A.maxLine = max(A.maxLine, length);
                length = 0;
                A.lines++;
            } else {
                length++;
            }
            if (ch != ' ' && ch != '\t' && ch != '\n' && !flag) {
                A.words++;
                flag = 1;
            }
            if (ch == ' ' || ch == '\t' || ch == '\n') flag = 0;
        }
        file.close();
    } else {
        A.exist = false;
    }
}

void CommandWC::run() {
    _c = _w = _l = _L = _w = false;
    for (int i = 0 ; i < files.size(); ++i) {
        contents.push_back(Content(files[i]));
        count(contents[i]);
    }
    if (opt.empty()) {
        _c = _w = _l = true;
    } else for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "-c") {
            _c = true;
        }
        if (opt[i] == "-m") {
            _m = true;
        }
        if (opt[i] == "-l") {
            _l = true;
        }
        if (opt[i] == "-L") {
            _L = true;
        }
        if (opt[i] == "-w") {
            _w = true;
        }
        if (opt[i] == "--help") {

        }
    }
    total = Content("total");
    for (int i = 0; i < contents.size(); ++i) {
        if (contents[i].exist) {
           if (_l) cout << contents[i].lines << ' ';
           if (_w) cout << contents[i].words << ' ';
           if (_c) cout << contents[i].bytes << ' ';
           if (_m) cout << contents[i].chars << ' ';
           if (_L) cout << contents[i].maxLine << ' ';
           cout << contents[i].file << endl;
   
           total.lines += contents[i].lines;
           total.words += contents[i].words;
           total.bytes += contents[i].bytes;
           total.chars += contents[i].chars;
           total.maxLine = max(total.maxLine, contents[i].maxLine);
        } else cout << "wc: " << contents[i].file << ": No such file or directory" << endl;
    }
    if (contents.size() > 1) {
        if (_l) cout << total.lines << ' ';
        if (_w) cout << total.words << ' ';
        if (_c) cout << total.bytes << ' ';
        if (_m) cout << total.chars << ' ';
        if (_L) cout << total.maxLine << ' ';
        cout << total.file << endl;
    }
}
