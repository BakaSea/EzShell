#ifndef COMMANDWC_H
#define COMMANDWC_H
#include "CommandBase.h"
#include <string>
using namespace std;

class CommandWC : public CommandBase {
public:
    CommandWC(string str);
    ~CommandWC();
    void run();
private:
    struct Content {
        int bytes, chars, lines, maxLine, words;
        bool exist;
        string file;
        Content() {  }
        Content(string file) : file(file), bytes(0), chars(0), lines(0), maxLine(0), words(0), exist(true) {  }
    };
    vector<Content> contents;
    Content total;
    bool _c, _m, _l, _L, _w;
    void count(Content &A);
};

#endif
