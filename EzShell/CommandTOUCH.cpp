#include "CommandTOUCH.h"
#include "CommandMAN.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
using namespace std;

CommandTOUCH::CommandTOUCH(string str, DirHelper *dirHelper) : CommandBase("touch", str, dirHelper) {
    help =
"Usage: touch FILE... \n\
Update the access and modification times of each FILE to the current time.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\
      --help     display this help and exit\n";
}

CommandTOUCH::~CommandTOUCH() {

}

void CommandTOUCH::run() {
    if (!analyzeOpt()) return;
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