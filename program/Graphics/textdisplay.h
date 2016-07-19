#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>


// _abc_ means abc is a the name of a field / variable


// class TextDisplay: the text display of the program

class TextDisplay{
    
	// matrix of char, representing the board
	char ** theTextDisplay;  

public:
	
    TextDisplay();		// constructor
    ~TextDisplay();		// destructor
	
	// public method, reset all char to ' '
    void clear();
	
	// public method, change the char at row _x_ col _y_ to _c_
    void notify (int x, int y, char c);
	
	// public method, clear line _n_
	void clearLine(int n);
	
	// to print out _theTextDisplay_; overloading friend operator <<
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
	
	// allow Graphic to access _theTextDisplay_ and update its graph
	friend class Graphic;
    
};


#endif