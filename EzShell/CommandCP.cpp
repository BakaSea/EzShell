#include "CommandCP.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>
using namespace std;

CommandCP::CommandCP(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

}

CommandCP::~CommandCP() {

}

void CommandCP::copy(string src, string dest, string direct) {
    string pathSrc = dirHelper->getPath()+"/"+src;
    string pathDirect = dirHelper->getPath()+"/"+direct;
    string pathDest = pathDirect+"/"+dest;
    struct stat path;
    stat(pathSrc.c_str(), &path);
    if (S_ISDIR(path.st_mode)) {
        if (_r) {
            DIR *dir = opendir(pathDirect.c_str());
            if (dir == NULL) {
                if (mkdir(pathDirect.c_str(), 0755)) {
                    cout << "cp: cannot create directory \'" << direct << "\': No such file or directory" << endl;
                    return;
                }
            }
            copyDir(pathSrc, pathDirect);
        } else cout << "cp: -r not specified; omitting directory \'" << src << "\'" << endl;
    } else {
        copyFile(pathSrc, pathDest);
    }
}

void CommandCP::copyFile(string src, string dest) {
    ifstream in(src, ios::in | ios::binary);
    if (in) {
        ifstream tryOut(dest, ios::out | ios::binary);
        if (tryOut) {
            if (_i) {
                cout << "cp: overwrite \'";
                for (int i = dirHelper->getPath().size()+1; i < dest.size(); ++i) {
                    cout << dest[i];
                }
                cout << "\'? ";
                string ans;
                getline(cin, ans);
                if (!(ans.size() == 1 && (ans[0] == 'Y' || ans[0] == 'y'))) {
                    tryOut.close();
                    return;
                }
            }
            tryOut.close();
        }
        in.seekg(0, ios::end);
        int size = in.tellg();
        char *buffer = new char[size];
        in.seekg(0, ios::beg);
        in.read(buffer, size);
        in.close();
        ofstream out(dest, ios::out | ios::binary);
        if (out) {
            out.write(buffer, size);
            out.close();
        } else cout << "Copy file failed" << endl;
    } else {
        cout << "cp: cannot stat \'";
        for (int i = dirHelper->getPath().size()+1; i < src.size(); ++i) {
            cout << src[i];
        }
        cout <<  "\': No such file or directory" << endl;
    }
}

void CommandCP::copyDir(string src, string direct) {
    DIR *dirSrc = opendir(src.c_str());
    if (dirSrc != NULL) {
        dirent *file;
        while (file = readdir(dirSrc)) {
            if (file->d_type == DT_DIR && strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
                string pathDir = direct+"/"+file->d_name;
                DIR *dirCur = opendir(pathDir.c_str());
                if (dirCur == NULL) {
                    if (mkdir(pathDir.c_str(), 0755)) {
                        cout << "Create directory failed" << endl;
                        return;
                    }
                }
                copyDir(src+"/"+file->d_name, pathDir);
            }
            if (file->d_type == DT_REG) {
                copyFile(src+"/"+file->d_name, direct+"/"+file->d_name);
            }
        }
        closedir(dirSrc);
    } else {
        cout << "cp: cannot stat \'";
        for (int i = dirHelper->getPath().size()+1; i < src.size(); ++i) {
            cout << src[i];
        }
        cout <<  "\': No such file or directory" << endl;
    }
}

void CommandCP::run() {
    _r = _i = false;
    _f = true;
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "-r") {
            _r = true;
        } else if (opt[i] == "-f") {
            _f = true;
        } else if (opt[i] == "-i") {
            _i = true;
        } else if (opt[i] == "--help") {

        } else {
            cout << "cp: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'cp --help\' for more information" << endl;
            return;
        }
    }
    if (files.empty()) {
        cout << "cp: missing file operand" << endl;
        cout << "Try \'cp --help\' for more information" << endl;
    } else {
        mk.clear();
        mk.push_back(1);
        for (int i = 0, j = 1; j < files.size(); ++j) {
            if (files[i][files[i].size()-1] == '\\') {
                files[i].pop_back();
                files[i] += " "+files[j];
                mk.push_back(0);
            } else {
                i = j;
                mk.push_back(1);
            }
        }
        cpFile.clear();
        for (int i = 0; i < files.size(); ++i) {
            if (mk[i]) {
                cpFile.push_back(files[i]);
            }
        }
        if (cpFile.size() == 1) {
            cout << "cp: missing destination file operand after \'" << cpFile[0] << "\'" << endl;
            cout << "Try \'cp --help\' for more information" << endl;
        } else if (cpFile.size() == 2) {
            struct stat pathDest;
            stat((dirHelper->getPath()+"/"+cpFile[1]).c_str(), &pathDest);
            if (S_ISDIR(pathDest.st_mode)) {
                copy(cpFile[0], cpFile[0], cpFile[1]);
            } else {
                struct stat pathSrc;
                stat((dirHelper->getPath()+"/"+cpFile[0]).c_str(), &pathSrc);
                if (S_ISDIR(pathSrc.st_mode)) {
                    copy(cpFile[0], cpFile[0], cpFile[1]);
                } else {
                    copy(cpFile[0], cpFile[1], "");
                }
            }
        } else {
            struct stat path;
            stat((dirHelper->getPath()+"/"+cpFile[cpFile.size()-1]).c_str(), &path);
            if (S_ISDIR(path.st_mode)) {
                for (int i = 0; i < cpFile.size()-1; ++i) {
                    copy(cpFile[i], cpFile[i], cpFile[cpFile.size()-1]);
                }
            } else {
                cout << "cp: target \'" << cpFile[cpFile.size()-1] << "\' is not a directory" << endl;
            }
        }
    }
}