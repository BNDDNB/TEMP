#include "textdisplay.h"

using namespace std;


// _abc_ means abc is a the name of a field / variable


// default constructor: initializing TextDisplay to empty grid
TextDisplay::TextDisplay() {
    theTextDisplay = new char *[15];
    for (int i = 0; i< 15; i++) {
        theTextDisplay[i] = new char [10];
		for (int j = 0; j < 10; j++) {
            theTextDisplay[i][j] = ' ';
        }
	}
}


// destructor: deleting TextDisplay
TextDisplay::~TextDisplay() {
	for(int i = 0; i < 15; i++) {
        delete [] theTextDisplay[i];
	}
    delete [] theTextDisplay;
}


// clear the grid, reset all char to ' ' 
void TextDisplay::clear() {
    for (int i = 0; i< 15; i++) {
		for (int j = 0; j < 10; j++) {
            theTextDisplay[i][j] = ' ';
        }
	}
}


// change the char at row _x_ col _y_ to _c_
void TextDisplay::notify(int x, int y, char c) {
    theTextDisplay[x][y] = c;
}


// clear line _n_
void TextDisplay::clearLine(int n) {
	delete [] theTextDisplay[n];	// delete line n
    int i;
	// for line _i_ < _n_, move the pointer to shift the line 
	for (i = n; i > 0; i -= 1) {
		theTextDisplay[i] = theTextDisplay[i-1]; 
	}
	// generate a new row at the top
	theTextDisplay[i] = new char[10];
	for (int j = 0; j < 10; j++) {
		theTextDisplay[i][j] = ' ';
	}
}


// overload friend operator << to print out text display
std::ostream &operator<< (std::ostream &out, const TextDisplay &t) {
    out << "----------" << endl;
	for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++){
            out << t.theTextDisplay[i][j];
        }
        out << endl;
    }
	out << "----------";
    return out;
}