
#include "coords.h"
using namespace std;


// to initialize theChar to ' ' and aBlock to NULL
Coords::Coords() {  
	theChar = ' ';
    aBlock = 0;
}


// Delete a coords. Depending on the value of live coords of a
//    block, it may or may not delete the block it points to
Coords::~Coords() {}


// to udpate the text display
void Coords::notifyDisplay(int x, int y, TextDisplay &d) {
    d.notify(x, y, theChar);
}

// to udpate the graphic display
void Coords::notifyGraphic(int x, int y, Graphic &g) {
    g.notify(x, y, theChar);
}



// during a movement, replace aChar with a new one
void Coords::change(char aChar) {    
    theChar = aChar;
}


char Coords::getChar() {
    return theChar;
}


// this function will return the level of the block that
//    this coords points to
int Coords::returnLevel() {
	return aBlock->getlvl();
}


// this function will return the number of alive coords
//    in the block that this coords points to
int Coords::returnNumAlive() {
    if (aBlock) {
        return aBlock->getliveCoords();
    }
    return -1;
}


// When block is dropped, a pointer to the block is passed
//    to coords for future operations
void Coords::linkBlock(Block *theBlock) {
	aBlock = theBlock;
}

// When the block is about to be deleted, notify the block it links to
void Coords::notifyBlock() {
    if (aBlock) {
        aBlock->notify();
    }
}

// Delete the block it links to
void Coords::deleteBlock() {
	if (aBlock) {
        delete aBlock;   
    }
}