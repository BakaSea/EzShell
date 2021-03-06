#include "CommandINSTALL.h"
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
using namespace std;

CommandINSTALL::CommandINSTALL(string str, DirHelper *dirHelper, unordered_map<string, bool> *mapCom) : 
    CommandBase("install", str, dirHelper), mapCom(mapCom) {
    help =
"Usage: install COMMAND FILE\n\
Install a command written by EzShell API.";
}

CommandINSTALL::~CommandINSTALL() {
    mapCom = NULL;
    delete mapCom;
}

void CommandINSTALL::run() {
    if (!analyzeOpt()) return;
    if (files.empty()) {
        cout << "install: no command!" << endl;
    } else if (files.size() == 1) {
        cout << "install: no command path!" << endl;
    } else {
        unordered_map<string, bool>::iterator iter = mapCom->find(files[0]);
        if (iter != mapCom->end()) {
            cout << "install: " << files[0] << " exists!" << endl;
        } else {
            if (!access(dirHelper->getFilePath(files[1]).c_str(), X_OK)) {
                DIR *dir = opendir("addons");
                if (dir == NULL) {
                    if (mkdir("addons", 0755)) {
                        cout << "install: cannot create addons directory" << endl;
                        return;
                    }
                }
                closedir(dir);
                struct stat path;
                stat(dirHelper->getFilePath(files[1]).c_str(), &path);
                if (S_ISDIR(path.st_mode)) {
                    cout << "install: \'" << files[1] << "\': is a directory" << endl;
                    return;
                }
                ifstream inAdd(dirHelper->getFilePath(files[1]), ios::in | ios::binary);
                if (inAdd) {
                    inAdd.seekg(0, ios::end);
                    int size = inAdd.tellg();
                    char *buffer = new char[size];
                    inAdd.seekg(0, ios::beg);
                    inAdd.read(buffer, size);
                    inAdd.clear();
                    ofstream outAdd("addons/"+files[0]);
                    if (outAdd) {
                        outAdd.write(buffer, size);
                        outAdd.close();
                    } else {
                        cout << "install: copy addons failed" << endl;
                        return;
                    }
                } else {
                    cout << "install: copy addons failed" << endl;
                    return;
                }
                if (chmod(("addons/"+files[0]).c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) {
                    cout << "install: permission denied" << endl;
                    return;
                }
                ofstream outCfg("addons/config.txt");
                if (outCfg) {
                    (*mapCom)[files[0]] = true;
                    for (unordered_map<string, bool>::iterator iter = mapCom->begin(); iter != mapCom->end(); ++iter) {
                        outCfg << iter->first << endl;
                    }
                    cout << "install: install successfully." << endl;
                } else {
                    cout << "install: cannot modify config" << endl;
                }
            } else {
                cout << "install: cannot add " << files[1] << endl;
            }
        }
    }
}