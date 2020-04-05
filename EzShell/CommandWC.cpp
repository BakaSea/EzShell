#include "CommandWC.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "CommandMAN.h"
using namespace std;

CommandWC::CommandWC(string str, DirHelper *dirHelper) : CommandBase("wc", str, dirHelper) {
    contents.clear();
}

CommandWC::~CommandWC() {
    contents.clear();
}

void CommandWC::count(Content &A) {
    struct stat path;
    stat((dirHelper->getPath()+"/"+A.file).c_str(), &path);
    if (S_ISDIR(path.st_mode)) {
        cout << "wc: " << A.file << ": Is a directory" << endl;
        return;
    }
    ifstream file(dirHelper->getPath()+"/"+A.file, ios::in | ios::binary);
    if (file) {
        file.seekg(0, ios::end);
        A.bytes = file.tellg();
        file.seekg(0, ios::beg);
        char *buffer = new char[A.bytes];
        file.read(buffer, A.bytes);
        for (int i = 0, length = 0, flag = 0; i < A.bytes; ++i) {
            if (buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\n' && !flag) {
                A.words++;
                flag = 1;
            }
            if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n') flag = 0;
            if (buffer[i] & 0x80) {
                A.chars++;
                length += 2;
                i += 2;
            } else {
                A.chars++;
                if (buffer[i] == '\n') {
                    A.maxLine = max(A.maxLine, length);
                    A.lines++;
                    length = 0;
                } else {
                    length++;
                }
            }
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
                        if (opt[i][j] == 'c') {
                            _c = true;
                        } else if (opt[i][j] == 'm') {
                            _m = true;
                        } else if (opt[i][j] == 'l') {
                            _l = true;
                        } else if (opt[i][j] == 'L') {
                            _L = true;
                        } else if (opt[i][j] == 'w') {
                            _w = true;
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
    total = Content("total");
    for (int i = 0; i < contents.size(); ++i) {
        if (contents[i].exist) {
           if (_l) cout << contents[i].lines << ' ';
           if (_w) cout << contents[i].words << ' ';
           if (_m) cout << contents[i].chars << ' ';
           if (_c) cout << contents[i].bytes << ' ';
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
