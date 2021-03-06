#include "CommandCMP.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "CommandMAN.h"
using namespace std;

CommandCMP::CommandCMP(string str, DirHelper *dirHelper) : CommandBase("cmp", str, dirHelper) {
    mapOpt["b"] = &_b;
    mapOpt["--print-bytes"] = &_b;
    mapOpt["l"] = &_l;
    mapOpt["--verbose"] = &_l;
    help = 
"Usage: cmp [OPTION]... FILE1 FILE2\n\
Compare two files byte by byte.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -b, --print-bytes          print differing bytes\n\
  -l, --verbose              output byte numbers and differing byte values\n\
      --help                 display this help and exit\n";
}

CommandCMP::~CommandCMP() {

}

int CommandCMP::convert(int x) {
    int res = 0, k = 1;
    while (x) {
        res += (x%8)*k;
        k *= 10;
        x /= 8;
    }
    return res;
}

void CommandCMP::run() {
    _b = _l = false;
    if (!analyzeOpt()) return;
    if (files.size() < 2) {
        cout << "Compared files are less than 2" << endl;
        return;
    }
    if (files.size() > 2) {
        cout << "Compared files are more than 2" << endl;
        return;
    }
    struct stat path1, path2;
    stat(dirHelper->getFilePath(files[0]).c_str(), &path1);
    stat(dirHelper->getFilePath(files[1]).c_str(), &path2);
    if (S_ISDIR(path1.st_mode)) {
        cout << "cmp: " << files[0] << ": Is a directory" << endl;
        return;
    }
    if (S_ISDIR(path2.st_mode)) {
        cout << "cmp: " << files[1] << ": Is a directory" << endl;
        return;
    }
    ifstream file1(dirHelper->getFilePath(files[0]), ios::in | ios::binary), file2(dirHelper->getFilePath(files[1]), ios::in | ios::binary);
    if (file1 && file2) {
        file1.seekg(0, ios::end);
        file2.seekg(0, ios::end);
        int size1 = file1.tellg(), size2 = file2.tellg();
        char *buffer1 = new char[size1], *buffer2 = new char[size2];
        file1.seekg(0, ios::beg);
        file2.seekg(0, ios::beg);
        file1.read(buffer1, size1);
        file2.read(buffer2, size2);
        if (!_l) {
            int size = min(size1, size2), flag = 0, line = 1;
            for (int i = 0; i < size; ++i) {
                if (buffer1[i] == '\n' && buffer2[i] == '\n') line++;
                if (buffer1[i] != buffer2[i]) {
                    cout << files[0] << " "  << files[1] << " differ: byte " << i+1 << ", line " << line;
                    if (_b) {
                        int c1 = convert(buffer1[i]), c2 = convert(buffer2[i]);
                        string s1 = string(), s2 = string();
                        s1.push_back(buffer1[i]);
                        s2.push_back(buffer2[i]);
                        if (buffer1[i] == '\n') s1 = "^J";
                        if (buffer1[i] == '\r') s1 = "^M";
                        if (buffer2[i] == '\n') s2 = "^J";
                        if (buffer2[i] == '\r') s2 = "^M";
                        cout << " is " << c1 << " " << s1 << " " << c2 << " " << s2;
                    }
                    cout << endl;
                    flag = 1;
                    break;
                }
            }
            if (!flag && size1 != size2) {
                cout << files[0] << " "  << files[1] << " differ: byte " << size << ", line " << line << endl;
            }
        } else {
            int size = min(size1, size2);
            for (int i = 0; i < size; ++i) {
                if (buffer1[i] != buffer2[i]) {
                    int c1 = convert(buffer1[i]), c2 = convert(buffer2[i]);
                    string s1 = string(), s2 = string();
                    s1.push_back(buffer1[i]);
                    s2.push_back(buffer2[i]);
                    if (buffer1[i] == '\n') s1 = "^J";
                    if (buffer1[i] == '\r') s1 = "^M";
                    if (buffer2[i] == '\n') s2 = "^J";
                    if (buffer2[i] == '\r') s2 = "^M";
                    if (_b) {
                        cout << i+1 << " " << c1 << " " << s1 << " " << c2 << " " << s2 << endl;
                    } else {
                        cout << i+1 << " " << c1 << " " << c2 << endl;
                    }
                }
            }
            if (size1 != size2) {
                cout << "cmp: EOF on " << (size1 < size2 ? files[0] : files[1]) << " after byte " << size << endl; 
            }
        }
        file1.close();
        file2.close();
    } else {
        if (!file1) cout << "cmp: " << files[0] << ": " << strerror(errno) << endl;
        if (!file2) cout << "cmp: " << files[1] << ": " << strerror(errno) << endl;
    }
}