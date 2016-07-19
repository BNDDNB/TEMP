//
//  coords.cc
//  
//
//  Created by Bonan Dong on 7/21/13.
//
//

class Block;
class Display;

#include "coords.h"

class Cell {
	Block *b;
	Coords position;
    char type;
    bool  isfull[15];
    
public:
    Cell(Coords myPosition, char blockType);
	void link(Block *b);
	void reset();
    void notifydisplay(Display &d);
    
    
    /*void drop(); //drops the whole grid by 1 line*/
}

