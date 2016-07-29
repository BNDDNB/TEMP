
#include "coords.h"
using namespace std;


// to initialize theChar to '_' and aBlock to NULL
Coords::Coords() {  
	theChar = '_';
    aBlock = 0;
}


// Delete a coords. Depending on the value of live coords of a
//    block, it may or may not delete the block it points to
Coords::~Coords() {}


// to udpate the text display
void Coords::notifyDisplay(int x, int y, Display &d) {
    d.notify(x, y, theChar);
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


/*
void notifywindow(int x, int y, Xwindow *aWindow)
{
    if (theChar == 'I')
    {
        draw (x * length, y * length, *aWindow, 1);
    }
    else if (theChar == 'Z')
    {
        draw(x * length, y* length, *aWindow, 2);
    }
    else if (theChar == 'J')
    {
        draw(x * length , y* length, *aWindow, 3);
    }
    else if (theChar == 'O')
    {
        draw(x * length , y* length, *aWindow, 4);
    }
    else if (theChar == 'S')
    {
        draw(x * length , y* length, *aWindow, 5); 
    }
    else if (theChar == 'L')
    {
        draw(x * length , y* length, *aWindow, 6); 
    }
    else if (theChar == 'T')
    {
        draw(x * length , y* length, *aWindow, 7); 
    }
    else
    {
        draw(x * length , y* length, *aWindow, 0);
    }
    
}
 
*/