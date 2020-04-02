#include "CommandCMP.h"
#include <iostream>
#include <fstream>

CommandCMP::CommandCMP(string str) : CommandBase(str) {
    
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
    if (files.size() < 2) {
        cout << "Compared files are less than 2" << endl;
        return;
    }
    if (files.size() > 2) {
        cout << "Compared files are more than 2" << endl;
        return;
    }
    _b = _l = false;
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "-b") {
            _b = true;
        } else if (opt[i] == "-l") {
            _l = true;
        }
    }
    ifstream file1(files[0], ios::in | ios::binary), file2(files[1], ios::in | ios::binary);
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
                        cout << " is " << convert(buffer1[i]) << " " << buffer1[i] << convert(buffer2[i]) << " " << buffer2[i];
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
                    if (_b) {
                        cout << i+1 << " " << convert(buffer1[i]) << " " << buffer1[i] << " " << convert(buffer2[i]) << " " << buffer2[i] << endl;
                    } else {
                        cout << i+1 << " " << convert(buffer1[i]) << " " << convert(buffer2[i]) << endl;
                    }
                }
            }
            cout << "cmp: EOF on " << (size1 < size2 ? files[0] : files[1]) << " after byte " << size << endl; 
        }
        file1.close();
        file2.close();
    } else {
        if (!file1) cout << "cmp: " << files[0] << ": No such file or directory" << endl;
        if (!file2) cout << "cmp: " << files[1] << ": No such file or directory" << endl;
    }
}