#ifndef ____DISPLAY_H____
#define ____DISPLAY_H____

#include <iostream>

class Display{
    
	char ** theDisplay;
public:
    Display();
    ~Display();
    void notify (int x, int y, char c);
	void clearLine(int n);
    friend std::ostream &operator<<(std::ostream &out, const Display &td);
};

#endif