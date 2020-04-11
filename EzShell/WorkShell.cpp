#include "WorkShell.h"
#include <fstream>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Command.h"

WorkShell::WorkShell(string str, DirHelper *dirHelper) : str(str), dirHelper(dirHelper) {

}

WorkShell::~WorkShell() {
    dirHelper = NULL;
    delete dirHelper;
}

void WorkShell::run() {
    int p = 0;
    while (str[p] == ' ' || str[p] == '\t') p++;
    if (str[p] == '.') p += 2;
    else {
        p += 2;
        while (p < str.size() && (str[p] == ' ' || str[p] == '\t')) p++;
    }
    if (p >= str.size()) {
        cout << "Please input file name!" << endl;
        return;
    }
    fileName.clear();
    for (int i = p, flag = 0; i < str.size(); ++i) {
        if (str[i] == ' ' && !flag) {
            break;
        }
        flag = 0;
        if (str[i] == '\\') {
            flag = 1;
        } else {
            fileName.push_back(str[i]);
        }
    }
    struct stat path;
    stat(dirHelper->getFilePath(fileName).c_str(), &path);
    if (S_ISDIR(path.st_mode)) {
        cout << "\'" << fileName << "\': is a directory." << endl;
        return;
    }
    ifstream in(dirHelper->getFilePath(fileName));
    if (in) {
        if (access(dirHelper->getFilePath(fileName).c_str(), X_OK)) {
            cout << "\'" << fileName << "\': permission denied" << endl;
            in.close();
            return;
        }
        string s;
        Command *command = new Command(dirHelper);
        while (getline(in, s)) {
            int k = command->find(s);
            if (!k) {
                cout << "Unknown command." << endl;
            } else if (k == -1) {
                break;
            } else if (k == -3) {
                WorkShell *shell = new WorkShell(s, dirHelper);
                shell->run();
            } else if (k != -2) {
                command->run();
            }
        }
        in.close();
    } else cout << fileName << ": " << strerror(errno) << endl;
}