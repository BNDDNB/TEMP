#ifndef ____COORDS_H____
#define ____COORDS_H____

#include "block.h"
#include "textdisplay.h"
#include "graphic.h"

class Coords {
    
	char theChar;    // store the type of block
    Block *aBlock;   // store a pointer to a block
	
  public:
    Coords();        // constructor
	~Coords();		 // destructor
	
	void deleteBlock();	  // delete the block it links to
	void change(char c);  // set up the char value during a movement
	char getChar();       // accessor to the char value (type of bloc
	int returnLevel();      // accessor to the level at which the linked block is generated
	int returnNumAlive();   // accessor to the # of live coords of the linked block
    void notifyBlock();

	// when a block is dropped, link the cell to the block
	void linkBlock(Block *theBlock);     
	// notifies display to update its value
	void notifyDisplay(int ver, int hor, TextDisplay &d);
    void notifyGraphic(int ver, int hor, Graphic &g);
    
    
	
};

#endif