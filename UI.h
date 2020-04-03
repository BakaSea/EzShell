#ifndef UI_H
#define UI_H
#include "Command.h"

class UI {
public:
    UI();
    ~UI();
    void show();
private:
    Command *command;
};

#endif
