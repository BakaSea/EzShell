#include "DirHelper.h"
#include "CommandBase.h"

int main(int argc, char *argv[]) {
    if (argc < 3) return -1;
    DirHelper *dirHelper = new DirHelper();
    dirHelper->setPath(argv[2]);
    CommandBase *command = NULL;
    //TODO: command = new CommandXXX(argv[1], dirHelper);
    if (command != NULL) command->run();
    return 0;
}
