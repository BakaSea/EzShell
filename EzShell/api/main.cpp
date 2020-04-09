#include "Command.h"
#include "DirHelper.h"

int main(int argc, char *argv[]) {
    if (argc < 3) return -1;
    DirHelper *dirHelper = new DirHelper();
    dirHelper->setPath(argv[2]);
    Command *command = new Command(dirHelper);
    int k = command->find(argv[1]);
    if (k) command->run();
    else return -1;
    return 0;
}
