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
        cout << "rm: remove \'";
        for (int i = dirHelper->getPath().size()+1; i < str.size(); ++i) {
            cout << str[i];
        }
        cout << "\'? ";
        string ans;
        getline(cin, ans);
        if (!(ans.size() == 1 && (ans[0] == 'Y' || ans[0] == 'y'))) {
            return 0;
        }
    }
    if (remove(str.c_str())) {
        cout << "rm: cannot remove \'";
        for (int i = dirHelper->getPath().size()+1; i < str.size(); ++i) {
            cout << str[i];
        }
        cout << "\': No such file or directory" << endl;
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
            if (file->d_type == DT_DIR && strcmp(file->d_name, ".") && strcmp(file->d_name, "..")) {
                flag |= removeDir(str+"/"+file->d_name);
            }
            if (file->d_type == DT_REG) {
                flag |= removeFile(str+"/"+file->d_name);
            }
        }
    } else {
        cout << "rm: cannot remove \'";
        for (int i = dirHelper->getPath().size()+1; i < str.size(); ++i) {
            cout << str[i];
        }
        cout <<  "\': No such file or directory" << endl;
    }
    if (flag) {
        if (_i) {
            cout << "rm: remove directory \'";
            for (int i = dirHelper->getPath().size()+1; i < str.size(); ++i) {
                cout << str[i];
            }
            cout << "\'? ";
            string ans;
            getline(cin, ans);
            if (!(ans.size() == 1 && (ans[0] == 'Y' || ans[0] == 'y'))) {
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
        stat((dirHelper->getPath()+"/"+files[i]).c_str(), &dir);
        if (S_ISDIR(dir.st_mode)) {
            if (_r) {
                removeDir(dirHelper->getPath()+"/"+files[i]);
            } else cout << "rm: cannot remove \'" << files[i] << "\': Is a directory" << endl;
        } else {
            removeFile(dirHelper->getPath()+"/"+files[i]);
        }
    }
}