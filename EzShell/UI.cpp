#include "UI.h"
#include <iostream>
#include <string>
#include "DirHelper.h"
using namespace std;

UI::UI() {

}

UI::~UI() {
    delete command;
}

void UI::show() {
    DirHelper *dirHelper = new DirHelper();
    dirHelper->initPath();
    command = new Command(dirHelper);
    string str;
    cout << "Welcome!" << endl;
    cout << "$ ";
    while (getline(cin, str)) {
        int k = command->find(str);
        if (!k) {
            cout << "Unknown command." << endl;
        } else if (k == -1) {
            break;
        } else if (k != -2) {
            command->run();
        }
        cout << "$ ";
    }
}
