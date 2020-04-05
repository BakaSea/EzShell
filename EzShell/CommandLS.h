#ifndef COMMANDLS_H
#define COMMANDLS_H
#include "CommandBase.h"
#include "DirHelper.h"
#include <string>
#include <vector>
#include <time.h>
#include <sys/stat.h>
using namespace std;

class CommandLS : public CommandBase {
    struct DirFile {
        string name;
        unsigned char type;
        struct stat status;
        DirFile(string name = "") : name(name) { }
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
    bool _a, _A, _l, _t, _r;
    vector<Content> contents;
    const string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    static bool cmpByName(const DirFile &A, const DirFile &B);
    static bool cmpByNameR(const DirFile &A, const DirFile &B);
    static bool cmpByTime(const DirFile &A, const DirFile &B);
    static bool cmpByTimeR(const DirFile &A, const DirFile &B);
    void getInfo(string str);
    void print(DirFile file);
    void show();
};

#endif