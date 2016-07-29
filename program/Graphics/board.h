#ifndef ____board__
#define ____board__

#include <iostream>
#include "block.h"
#include "coords.h"
#include "textdisplay.h"
#include "graphic.h"
#include "nextblock.h"

class Board{
	Coords **theCoords;
	NextBlock *next;            //ptr to factory
    TextDisplay *theDisplay;    //connect with text display
	Graphic *theGraphic;        //connect with graphical display
    Block *theBlock;            //connect with active block
	Block *newBlock;            //next block
    int ver, hor;               //bottom left corner
	int level;
	int score, hiScore;
    bool isFull[15];            //which line is full
    bool gameOver;              //if game is over
    void placecharhlpr(const char cmd);     //this hlpr fn places
                                            //char
    
    bool checkcharhlpr();                   //this hlpr fn checks
                                            //if can mv
    void NextBlockGraph(const char cmd);
    bool isSameB();                         //making sure that
                                            // the current block is the same
                                            //as the one it points to
    
	void addScore(int toAdd);               //scoring algorithm
        
    void isFullfn();                        //checking if the line is full
    
    void clearLine(int startLine, int numLine);//clears the line thats full
                                            // and return # of line it cleared.
public:
    Board(int presetlevel, NextBlock *nextb);
	~Board();
    void restart(int level);
    void setGraphic();
    void left();                //mv to the left
    void right();               //mv to the right
    void down();                //mv down
    void drop();                //drops the block need to reset the coords.
    void rotlef();              //rotate counterclockwise
    void rotrig();              //rotate clockwise
	void levelup();             //increase level by 1
	void leveldown();           //decrease level by 1
	void setLevel(int l);       //setting the starting level
    
    
    friend std::ostream &operator<<(std::ostream &out, const Board &td);
};

#endif
