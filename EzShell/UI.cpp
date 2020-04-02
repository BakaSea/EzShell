#include "UI.h"
#include <iostream>
#include <string>
using namespace std;

UI::UI() {
    command = new Command();
}

UI::~UI() {
    delete command;
}

void UI::show() {
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
