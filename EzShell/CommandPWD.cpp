#include "CommandPWD.h"
#include "CommandMAN.h"

CommandPWD::CommandPWD(string str, DirHelper *dirHelper) : CommandBase("pwd", str, dirHelper) {
    help =
"pwd: pwd\n\
    Print the name of the current working directory.\n";
}

CommandPWD::~CommandPWD() {

}

void CommandPWD::run() {
    if (!analyzeOpt()) return;
    cout << dirHelper->getPath() << endl;
}