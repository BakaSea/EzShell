#include "CommandTOUCH.h"
#include "CommandMAN.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
using namespace std;

CommandTOUCH::CommandTOUCH(string str, DirHelper *dirHelper) : CommandBase("touch", str, dirHelper) {

}

CommandTOUCH::~CommandTOUCH() {

}

void CommandTOUCH::run() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i].size() > 1) {
            if (opt[i][0] == '-') {
                if (opt[i][1] == '-') {
                    if (opt[i] == "--help") {
                        CommandMAN *man = new CommandMAN("man "+name, dirHelper);
                        man->run();
                        return;
                    } else {
                        cout << name << ": unrecognized option \'" << opt[i] << "\'" << endl;
                        cout << "Try \'" << name << " --help\' for more information" << endl;
                        return;
                    }
                } else {
                    for (int j = 1; j < opt[i].size(); ++j) {
                        cout << name << ": unrecognized option \'" << opt[i][j] << "\'" << endl;
                        cout << "Try \'" << name << " --help\' for more information" << endl;
                        return;
                    }
                }
            }
        }
    }
    if (files.empty()) {
        cout << "touch: missing file operand" << endl;
        cout << "Try \'touch --help\' for more information." << endl;
    } else for (int i = 0; i < files.size(); ++i) {
        struct stat file;
        stat((dirHelper->getPath()+"/"+files[i]).c_str(), &file);
        if (S_ISDIR(file.st_mode)) continue;
        ifstream in(dirHelper->getPath()+"/"+files[i], ios::in | ios::binary);
        if (in) {
            in.seekg(0, ios::end);
            int size = in.tellg();
            in.seekg(0, ios::beg);
            char *buffer = new char[size];
            in.read(buffer, size);
            in.close();
            ofstream out(dirHelper->getPath()+"/"+files[i], ios::out | ios::binary);
            if (out) {
                out.write(buffer, size);
                out.close();
            } else cout << "Cannot touch " << files[i] << endl;
        } else {
            ofstream out(dirHelper->getPath()+"/"+files[i]);
            if (out) {
                out.close();
            } else cout << "Cannot touch " << files[i] << endl;
        }
    }
}