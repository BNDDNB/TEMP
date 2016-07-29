#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <iostream>
#include <string>

#include "window.h"
#include "textdisplay.h"


// _abc_ means abc is a the name of a field / variable


// class Graphic: the graphic component of the program

class Graphic {
	
    TextDisplay *const d;  // pointer to display
    Xwindow *w;			   // pointer to graphic 
	
	// private method: choose the color code according to block type _type_
	int chooseColor(char type) const;
	
	// private method: convert int to string (for printing numbers)
    std::string int_to_str(const int& theInt) const;

 public:
	
    Graphic(TextDisplay *theDis);		// constructor
    ~Graphic();							// destructor
	
	// public method, initializing the graphic component
    void init(int lvl, int scr, int hiScr);
	
	// to be called by Board: restart the display of Board ONLY 
    void restart();
    
	// to be called by Board: update _lvl_
	void notifyLevel(int lvl);
	
	// to be called by Board: update _scr_ and _hiScr_
    void notifyScore(int scr, int hiScr);
	
	// to be called by Board to update the graphic of the board which
	// corresponds to the Coords at row _x_ col _y_ with type char _type_
	void notify(int x, int y, char type);
	
	// to be called by Board to update the graphic of next block which corresponds
	// to the char at row _x_ col _y_ of the block pattern, with type _type_
	void notifyNext(int x, int y, char type);
	
	// clear line _lineNum_
    void clearLine(int lineNum);
	
};


#endif