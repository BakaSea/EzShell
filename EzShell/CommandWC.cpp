#include "CommandWC.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "CommandMAN.h"
using namespace std;

CommandWC::CommandWC(string str, DirHelper *dirHelper) : CommandBase("wc", str, dirHelper) {
    mapOpt["c"] = &_c;
    mapOpt["--bytes"] = &_c;
    mapOpt["m"] = &_m;
    mapOpt["--chars"] = &_m;
    mapOpt["l"] = &_l;
    mapOpt["--lines"] = &_l;
    mapOpt["L"] = &_L;
    mapOpt["--max-line-length"] = &_L;
    mapOpt["w"] = &_w;
    mapOpt["--words"] = &_w;
    help =
"Usage: wc [OPTION]... [FILE]...\n\
Print newline, word, and byte counts for each FILE, and a total line if\n\
more than one FILE is specified.  A word is a non-zero-length sequence of\n\
characters delimited by white space.\n\n\
The options below may be used to select which counts are printed, always in\n\
the following order: newline, word, character, byte, maximum line length.\n\
  -c, --bytes            print the byte counts\n\
  -m, --chars            print the character counts\n\
  -l, --lines            print the newline counts\n\
  -L, --max-line-length  print the maximum display width\n\
  -w, --words            print the word counts\n\
      --help     display this help and exit\n";
}

CommandWC::~CommandWC() {
    contents.clear();
}

void CommandWC::count(Content &A) {
    struct stat path;
    stat(dirHelper->getFilePath(A.file).c_str(), &path);
    if (S_ISDIR(path.st_mode)) {
        cout << "wc: " << A.file << ": Is a directory" << endl;
        return;
    }
    ifstream file(dirHelper->getFilePath(A.file), ios::in | ios::binary);
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
    contents.clear();
    for (int i = 0 ; i < files.size(); ++i) {
        contents.push_back(Content(files[i]));
        count(contents[i]);
    }
    if (opt.empty()) {
        _c = _w = _l = true;
    } else {
        if (!analyzeOpt()) return;
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
        } else cout << "wc: failed to wc \'" << contents[i].file << "\'" << endl;
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
