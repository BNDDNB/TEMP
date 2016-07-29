#ifndef ____board__
#define ____board__

#include <iostream>
#include "block.h"
#include "coords.h"
#include "display.h"
#include "nextblock.h"

class Board{
    
	Coords **theCoords;
	NextBlock *next;
    Display *theDisplay;
	//Graphic *theGraphic;
    Block *theBlock;
	Block *newBlock;
    int ver, hor;
	int level;
	int score, hiScore;
    bool isFull[15];
	
public:
    Board(int presetlevel, NextBlock *nextb);
	~Board();
    void restart(int level);
    void left();    //mv to the left
    void right();   //mv to the right
    void down();    //mv down
    void drop();   //drops the block need to reset the coords.
    void rotlef();
    void rotrig();
	void levelup();
	void leveldown();
	void setLevel(int l);
    void isFullfn();   //checking if the line is full
    void clearLine(int startLine, int numLine);//clears the line thats full and return # of line it cleared.
    bool isSameB();
	void addScore(int toAdd);
	void placecharhlpr(char cmd);   //this hlpr fn places char
    bool checkcharhlpr();   //this hlpr fn checks if can mv
    friend std::ostream &operator<<(std::ostream &out, const Board &td);
};

#endif
