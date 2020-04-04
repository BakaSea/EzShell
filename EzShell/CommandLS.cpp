#include "CommandLS.h"
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <algorithm>
#include "CommandMAN.h"

CommandLS::CommandLS(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

}

CommandLS::~CommandLS() {
    contents.clear();
}

void CommandLS::getInfo(string str) {
    Content cur(str);
    DIR *dir = opendir((dirHelper->getPath()+"/"+str).c_str());
    if (dir == NULL) {
        ifstream file(dirHelper->getPath()+"/"+str);
        if (file) {
            cur.type = 1;
        } else {
            cur.failed = 1;
        }
    } else {
        dirent *file;
        while (file = readdir(dir)) {
            cur.file.push_back(DirFile(file->d_name));
        }
        closedir(dir);
    }
    contents.push_back(cur);
}

void CommandLS::show() {
    sort(contents.begin(), contents.end());
    if (contents.size() == 1) {
        if (contents[0].failed) {
            cout << "ls: cannot access \'" << contents[0].name << "\': No such file or directory" << endl;
        } else {
            sort(contents[0].file.begin(), contents[0].file.end());
            for (int i = 0; i < contents[0].file.size(); ++i) {
                cout << contents[0].file[i].name << " ";
            }
            cout << endl;
        }
    } else for (int i = 0; i < contents.size(); ++i) {
        if (contents[i].failed) {
            cout << "ls: cannot access \'" << contents[i].name << "\': No such file or directory" << endl;
        } else {
            sort(contents[i].file.begin(), contents[i].file.end());
            for (int j = 0; j < contents[i].file.size(); ++j) {
                cout << contents[i].file[j].name << " ";
            }
            cout << endl;
        }
    }
}

void CommandLS::run() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "--help") {
            CommandMAN *man = new CommandMAN("man ls", dirHelper);
            man->run();
            return;
        } else {
            cout << "ls: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'ls --help\' for more information" << endl;
            return;
        }
    }
    contents.clear();
    if (files.empty()) {
        getInfo(".");
    } else for (int i = 0; i < files.size(); ++i) {
        getInfo(files[i]);
    }
    show();
}