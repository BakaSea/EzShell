#include "WorkShell.h"
#include <fstream>
#include <iostream>
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
    p += 2;
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
    ifstream in(dirHelper->getFilePath(fileName));
    if (in) {
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
    } else cout << fileName << ": No such file or directory" << endl;
}