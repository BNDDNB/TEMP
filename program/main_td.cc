#include <iostream>
#include <string>
using namespace std;

#include "display.h"

int main () {
    
    Display *td = new Display();
    
    char command;
    while (cin >> command) {
        if (command == 'd') {
            delete td;
        } else if (command == 'n') {
            int d1, d2;
            char c;
            cin >> d1 >> d2 >> c;
            td->notify(d1,d2,c);
            
        } else if (command == 'c') {
            int n;
            cin >> n;
            td->clearLine(n);
        } else if (command == 'p') {
            cout << *td << endl;
        } else {
            break;
        }
    }
}
