#include "CommandOther.h"
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;

CommandOther::CommandOther(string str, DirHelper *dirHelper, string path) : CommandBase("other", str, dirHelper), path(path) {

}

CommandOther::~CommandOther() {

}

void CommandOther::run() {
    string dirPath = dirHelper->getPath();
    char **argv = new char*[4];
    argv[0] = new char[2];
    strcpy(argv[0], "a");
    argv[1] = new char[strSrc.size()];
    strcpy(argv[1], strSrc.c_str());
    argv[2] = new char[dirPath.size()];
    strcpy(argv[2], dirPath.c_str());
    argv[3] = new char;
    argv[3] = 0;
    int pid = fork();
    wait(NULL);
    if (pid == -1) {
        perror("fork failed");
    }
    if (pid == 0) {
        execvp(path.c_str(), argv);
        perror("execvp failed");
        exit(-1);
    }
}