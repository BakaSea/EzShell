#include "CommandPWD.h"

CommandPWD::CommandPWD(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

}

CommandPWD::~CommandPWD() {

}

void CommandPWD::run() {
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "--help") {

        } else {
            cout << "pwd: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'pwd --help\' for more information" << endl;
            return;
        }
    }
    cout << dirHelper->getPath() << endl;
}