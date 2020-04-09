#include "CommandINSTALL.h"
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
using namespace std;

CommandINSTALL::CommandINSTALL(string str, DirHelper *dirHelper, unordered_map<string, bool> *mapCom) : 
    CommandBase("install", str, dirHelper), mapCom(mapCom) {

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
            if (!access((dirHelper->getPath()+"/"+files[1]).c_str(), X_OK)) {
                DIR *dir = opendir((dirHelper->initPath()+"/addons").c_str());
                if (dir == NULL) {
                    if (mkdir((dirHelper->initPath()+"/addons").c_str(), 0755)) {
                        cout << "install: cannot create addons directory" << endl;
                        return;
                    }
                }
                closedir(dir);
                ifstream inAdd(dirHelper->getPath()+"/"+files[1], ios::in | ios::binary);
                if (inAdd) {
                    inAdd.seekg(0, ios::end);
                    int size = inAdd.tellg();
                    char *buffer = new char[size];
                    inAdd.seekg(0, ios::beg);
                    inAdd.read(buffer, size);
                    inAdd.clear();
                    ofstream outAdd(dirHelper->initPath()+"/addons/"+files[0]);
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
                if (chmod((dirHelper->initPath()+"/addons/"+files[0]).c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)) {
                    cout << "install: permission denied" << endl;
                    return;
                }
                ofstream outCfg(dirHelper->initPath()+"/addons/config.txt");
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