#ifndef COMMANDLS_H
#define COMMANDLS_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <string>
#include <vector>
using namespace std;

class CommandLS : public CommandBase {
    struct DirFile {
        string name;
        DirFile(string name = "") : name(name) { }
        bool operator < (const DirFile &A) const {
            return name < A.name;
        }
    };
    struct Content {
        string name;
        int type, failed;
        vector<DirFile> file;
        Content(string name = "") : name(name), type(type), failed(0) {
            file.clear();
        }
        bool operator < (const Content &A) const {
            return type > A.type;
        }
    };
public:
    CommandLS(string str, DirHelper *dirHelper);
    ~CommandLS();
    void run();
private:
    vector<Content> contents;
    void getInfo(string str);
    void show();
};

#endif