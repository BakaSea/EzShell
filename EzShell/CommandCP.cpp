#include "CommandCP.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>
#include "CommandMAN.h"
using namespace std;

CommandCP::CommandCP(string str, DirHelper *dirHelper) : CommandBase("cp", str, dirHelper) {
    mapOpt["i"] = &_i;
    mapOpt["--interactive"] = &_i;
    mapOpt["r"] = &_r;
    mapOpt["R"] = &_r;
    mapOpt["--recursive"] = &_r;
    help = 
"Usage: cp [OPTION]... [-T] SOURCE DEST\n\
  or:  cp [OPTION]... SOURCE... DIRECTORY\n\
Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -i, --interactive            prompt before overwrite (overrides a previous -n\n\
                                  option)\n\
  -R, -r, --recursive          copy directories recursively\n\
      --help     display this help and exit\n";
}

CommandCP::~CommandCP() {

}

void CommandCP::copy(string src, string dest, string direct) {
    string pathSrc = dirHelper->getFilePath(src);
    string pathDirect = dirHelper->getFilePath(direct);
    string pathDest = pathDirect+"/"+dest;
    struct stat path;
    stat(pathSrc.c_str(), &path);
    if (S_ISDIR(path.st_mode)) {
        if (_r) {
            DIR *dir = opendir(pathDirect.c_str());
            if (dir == NULL) {
                if (dirHelper->contain(pathSrc, pathDirect)) {
                    cout << "cp: cannot copy a directory, \'" << src << "\', into itself, \'" << pathDirect << "\'" << endl;
                    return;
                }
                if (mkdir(pathDirect.c_str(), 0755)) {
                    cout << "cp: cannot create directory \'" << direct << "\'" << endl;
                    return;
                }
                copyDir(pathSrc, pathDirect);
            } else {
                string pathDir = pathDirect+"/"+dirHelper->getFinalDir(src);
                DIR *dirDest = opendir(pathDir.c_str());
                if (dirHelper->contain(pathSrc, pathDir)) {
                    cout << "cp: cannot copy a directory, \'" << src << "\', into itself, \'" << pathDir << "\'" << endl;
                    return;
                }
                if (dirDest == NULL) {
                    if (mkdir(pathDir.c_str(), 0755)) {
                        cout << "cp: cannot create directory \'" << pathDir << "\'" << endl;
                        return;
                    }
                }
                copyDir(pathSrc, pathDir);
            }
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
                cout << "cp: overwrite \'" << dest << "\'? ";
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
            struct stat statSrc;
            stat(src.c_str(), &statSrc);
            chmod(dest.c_str(), statSrc.st_mode);
        } else {
            cout << "cp: copy file to \'" << dest << "\' failed" << endl;
        }
    } else {
        cout << "cp: cannot stat \'" << src << "\'" << endl;
    }
}

void CommandCP::copyDir(string src, string direct) {
    DIR *dirSrc = opendir(src.c_str());
    if (dirSrc != NULL) {
        dirent *file;
        while (file = readdir(dirSrc)) {
            if (file->d_type == DT_DIR) {
                if (strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
                    string pathDir = direct+"/"+file->d_name;
                    DIR *dirCur = opendir(pathDir.c_str());
                    if (dirCur == NULL) {
                        if (mkdir(pathDir.c_str(), 0755)) {
                            cout << "cp: create directory failed" << endl;
                            return;
                        }
                    }
                    copyDir(src+"/"+file->d_name, pathDir);
                }
            }
            if (file->d_type == DT_REG) {
                copyFile(src+"/"+file->d_name, direct+"/"+file->d_name);
            }
        }
        closedir(dirSrc);
    } else {
        cout << "cp: cannot stat \'" << src << "\': No such file or directory" << endl;
    }
}

void CommandCP::run() {
    _r = _i = false;
    if (!analyzeOpt()) return;
    if (files.empty()) {
        cout << "cp: missing file operand" << endl;
        cout << "Try \'cp --help\' for more information" << endl;
    } else {
        if (files.size() == 1) {
            cout << "cp: missing destination file operand after \'" << files[0] << "\'" << endl;
            cout << "Try \'cp --help\' for more information" << endl;
        } else if (files.size() == 2) {
            struct stat pathDest;
            stat(dirHelper->getFilePath(files[1]).c_str(), &pathDest);
            if (S_ISDIR(pathDest.st_mode)) {
                copy(files[0], files[0], files[1]);
            } else {
                struct stat pathSrc;
                stat(dirHelper->getFilePath(files[0]).c_str(), &pathSrc);
                if (S_ISDIR(pathSrc.st_mode)) {
                    copy(files[0], files[0], files[1]);
                } else {
                    copy(files[0], files[1], "");
                }
            }
        } else {
            struct stat path;
            stat(dirHelper->getFilePath(files[files.size()-1]).c_str(), &path);
            if (S_ISDIR(path.st_mode)) {
                for (int i = 0; i < files.size()-1; ++i) {
                    copy(files[i], files[i], files[files.size()-1]);
                }
            } else {
                cout << "cp: target \'" << files[files.size()-1] << "\' is not a directory" << endl;
            }
        }
    }
}