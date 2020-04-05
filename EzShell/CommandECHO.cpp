#include "CommandECHO.h"
#include <iostream>

CommandECHO::CommandECHO(string str, DirHelper *dirHelper) : CommandBase("echo", str, dirHelper) {

}

CommandECHO::~CommandECHO() {
    
}

void CommandECHO::run() {
    for (int i = 1; i < command.size(); ++i) {
        cout << command[i] << ' ';
    }
    cout << endl;
}
