#include <iostream>
#include <string>
using namespace std;

#include "block.h"

int main () {
    char command;
    Board b;
    while (cin >> command) {
        if (command == 'd') {
            delete b;
        } else if (command == 'n') {
            char c;
            cin >> c;
            if (c == 'i')
            {
                b = new BlockI(0);
            }
            else if ( c == 'j')
            {
                b = new BlockJ(0);
            }
            else if ( c == 'l')
            {
                b = new BlockL(0);
            }
            else if ( c == 'o')
            {
                b = new BlockO(0);
            }
            else if ( c == 'z')
            {
                b = new BlockZ(0);
            }
            else if ( c == 's')
            {
                b = new BlockS(0);
            }
            else if ( c == 't')
            {
                b = new BlockT(0);
            }
        } else if (command == 'r') {
            char c;
            cin >> c;
            if ( c == 'l')
            {
                b->counterclockwise();
            }
            else
            {
                b->clockwise();
            }
        } else if (command == 'p') {
            b->print();
        } else {
            break;
        }
    }
}
