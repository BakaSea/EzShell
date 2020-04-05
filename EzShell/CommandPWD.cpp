#include "CommandPWD.h"
#include "CommandMAN.h"

CommandPWD::CommandPWD(string str, DirHelper *dirHelper) : CommandBase("pwd", str, dirHelper) {

}

CommandPWD::~CommandPWD() {

}

void CommandPWD::run() {
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
    cout << dirHelper->getPath() << endl;
}