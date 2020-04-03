#include "CommandLS.h"
#include <iostream>
#include <dirent.h>
#include "CommandMAN.h"

CommandLS::CommandLS(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

}

CommandLS::~CommandLS() {

}

void CommandLS::show(string str) {
    DIR *dir = opendir((dirHelper->getPath()+"/"+str).c_str());
    if (dir == NULL) {
        cout << "ls: cannot access \'" << str << "\': No such file or directory" << endl;
        return;
    }
    dirent *file;
    while (file = readdir(dir)) {
        cout << file->d_name << " ";
    }
    cout << endl;
    closedir(dir);
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
    if (files.empty()) {
        show(".");
    } else for (int i = 0; i < files.size(); ++i) {
        show(files[i]);
    }
}