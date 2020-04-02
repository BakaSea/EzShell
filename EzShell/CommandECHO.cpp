#include "CommandECHO.h"
#include <iostream>

CommandECHO::CommandECHO(string str) : CommandBase(str) {

}

CommandECHO::~CommandECHO() {

}

void CommandECHO::run() {
    for (int i = 1; i < command.size(); ++i) {
        cout << command[i] << ' ';
    }
    cout << endl;
}
