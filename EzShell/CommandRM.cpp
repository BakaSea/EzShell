#include "CommandRM.h"
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
using namespace std;

CommandRM::CommandRM(string str, DirHelper *dirHelper) : CommandBase("rm", str, dirHelper) {
    mapOpt["i"] = &_i;
    mapOpt["r"] = &_r;
    mapOpt["R"] = &_r;
    mapOpt["--recursive"] = &_r;
    help =
"Usage: rm [OPTION]... [FILE]...\n\
Remove (unlink) the FILE(s).\n\n\
  -i                    prompt before every removal\n\
  -r, -R, --recursive   remove directories and their contents recursively\n\
      --help     display this help and exit\n";
}

CommandRM::~CommandRM() {
    
}

int CommandRM::removeFile(string str) {
    if (_i) {
        cout << "rm: remove \'" << str << "\'? ";
        string ans;
        getline(cin, ans);
        if (!(ans == "Y" || ans == "y" || ans == "yes" || ans == "Yes" || ans == "YES")) {
            return -1;
        }
    }
    if (remove(str.c_str())) {
        cout << "rm: cannot remove \'" << str << "\'" << endl;
        return -1;
    }
    return 0;
}

int CommandRM::removeDir(string str) {
    DIR *dir = opendir(str.c_str());
    int flag = 1;
    if (dir != NULL) {
        dirent *file;
        while (file = readdir(dir)) {
            if (file->d_type == DT_DIR) {
                if (strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
                    flag |= removeDir(str+"/"+file->d_name);
                }
            }
            if (file->d_type == DT_REG) {
                flag |= removeFile(str+"/"+file->d_name);
            }
        }
        closedir(dir);
    } else {
        cout << "rm: cannot remove \'" << str << "\'" << endl;
    }
    if (flag) {
        if (_i) {
            cout << "rm: remove directory \'" << str << "\'? ";
            string ans;
            getline(cin, ans);
            if (!(ans == "Y" || ans == "y" || ans == "yes" || ans == "Yes" || ans == "YES")) {
                return -1;
            }
        }
        flag |= remove(str.c_str());
    }
    return flag;
}

void CommandRM::run() {
    _r = _i = false;
    if (!analyzeOpt()) return;
    for (int i = 0; i < files.size(); ++i) {
        struct stat dir;
        stat(dirHelper->getFilePath(files[i]).c_str(), &dir);
        if (S_ISDIR(dir.st_mode)) {
            if (_r) {
                removeDir(dirHelper->getFilePath(files[i]));
            } else cout << "rm: cannot remove \'" << files[i] << "\': Is a directory" << endl;
        } else {
            removeFile(dirHelper->getFilePath(files[i]));
        }
    }
}