#include "CommandUNINSTALL.h"
#include <iostream>
#include <fstream>
using namespace std;

CommandUNINSTALL::CommandUNINSTALL(string str, DirHelper *dirHelper, unordered_map<string, bool> *mapCom) : 
    CommandBase("uninstall", str, dirHelper), mapCom(mapCom) {

}

CommandUNINSTALL::~CommandUNINSTALL() {
    mapCom = NULL;
    delete mapCom;
}

void CommandUNINSTALL::run() {
    if (!analyzeOpt()) return;
    if (files.empty()) {
        cout << "uninstall: require commands" << endl;
    } else {
        ofstream out(dirHelper->initPath()+"/addons/config.txt");
        if (out) {
            for (int i = 0; i < files.size(); ++i) {
                unordered_map<string, bool>::iterator iter = mapCom->find(files[i]);
                if (iter != mapCom->end()) {
                    if (iter->second) mapCom->erase(iter);
                    else cout << "uninstall: cannot uninstall " << files[i] << endl;
                } else {
                    cout << "uninstall: " << files[i] << " does not exist!" << endl;
                }
            }
            for (unordered_map<string, bool>::iterator iter = mapCom->begin(); iter != mapCom->end(); ++iter) {
                out << iter->first << endl;
            }
            out.close();
        } else {
            cout << "uninstall: cannot modify config" << endl;
        }
    }
}