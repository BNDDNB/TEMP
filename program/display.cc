#include "display.h"
using namespace std;

// initializing display to empty grid;
Display::Display() {
    theDisplay = new char *[15];
    for (int i = 0; i< 15; i++) {
        theDisplay[i] = new char [10];
		for (int j = 0; j < 10; j++) {
            theDisplay[i][j] = '_';
        }
	}
}

// deleting display
Display::~Display() {
	for(int i = 0; i < 15; i++) {
        delete [] theDisplay[i];
	}
    delete [] theDisplay;
}

// this changes char of destination to c
void Display::notify(int x, int y, char c) {
    theDisplay[x][y] = c;
}

// clear line n
void Display::clearLine(int n) {
	delete [] theDisplay[n];
    int i;
	for (i = n; i > 0; i -= 1) {
		theDisplay[i] = theDisplay[i-1]; 
	}
	theDisplay[i] = new char[10];
	for (int j = 0; j < 10; j++) {
		theDisplay[i][j] = '_';
	}
}

// overloading friendly operator <<
std::ostream &operator<< (std::ostream &out, const Display &t) {
    out << "----------" << endl;
	for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++){
            out << t.theDisplay[i][j];
        }
        out << endl;
    }
	out << "----------";
    return out;
}