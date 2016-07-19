#include "board.h"
#include <iostream>
using namespace std;

Board::Board(int presetlevel, NextBlock *nextb) {
    //initialize board
    theCoords = new Coords *[15];
    for (int i = 0; i < 15; i++) {
        theCoords[i] = new Coords[10];
    }
    
    //get NextBlock, generate desired blocks
    next = nextb;
    theDisplay = new Display();
    theBlock = next->getNext();
	newBlock = next->getNext();
    
    //setting up current location, level, scores etc.
    level = presetlevel;
    score = hiScore = 0;
    ver = 3;
    hor = 0;
    for (int i = 0; i < 15; i++) {
        isFull[i] = false;
    }

    //put the current block on the board
    placecharhlpr('p');
}

Board::~Board() {
	for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j += 1) {
            theCoords[i][j].notifyBlock();
            if (!theCoords[i][j].returnNumAlive()) {
                theCoords[i][j].deleteBlock();
            }
        }
        delete [] theCoords[i];
    }
	delete [] theCoords;

	delete theDisplay;
	delete theBlock;
	delete newBlock;
}

void Board::restart(int startLevel) {
	for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j += 1) {
            theCoords[i][j].notifyBlock();
            if (!theCoords[i][j].returnNumAlive()) {
                theCoords[i][j].deleteBlock();
            }
        }
        delete [] theCoords[i];
    }
	delete [] theCoords;
    delete theBlock;
	delete newBlock;
	
	theCoords= new Coords *[15];
    for (int i = 0; i < 15; i++) {
        theCoords[i] = new Coords [10];
    }
    
	setLevel(startLevel);
    next->restart();
	theBlock = next->getNext();
	newBlock = next->getNext();
    
	ver = 3;
    hor = 0;
	
	score = 0;
	
	delete theDisplay;
    theDisplay = new Display();

	for (int i = 0; i < 15; i++) {
        isFull[i] = false;
    }
    
    placecharhlpr('p');
}



void Board::left() {
    if(hor > 0 && isSameB()){
		placecharhlpr('r');  //clear up all chars
        hor --;              //movev to the left
		
		//try to place the block, and see if we can move it
        bool mv = checkcharhlpr();
		
        //if we can't, then we move it back
		//    then place it on the screen
        if (!mv) { hor ++; }
        placecharhlpr('p');
        cout<<ver<<' '<<hor<<' '<<mv<<' '<<isFull[ver]<<endl;
    }
}



// moving to the right is the very similar to moving to the left
void Board::right() {
    if(hor < 9 && isSameB()){
        placecharhlpr('r');  
        hor ++;
		bool mv = checkcharhlpr();
        if (!mv) { hor --; }
        placecharhlpr('p');
        cout<<ver<<' '<<hor<<' '<<mv<<' '<<isFull[ver]<<endl;
    }
}



void Board::rotlef() {
    if (isSameB()){
        placecharhlpr('r');           //clear up all chars
        theBlock->counterclockwise(); //rotate the block
    
        //try to place the block, and see if we can rotate it
        bool canrot = checkcharhlpr();
	
        //if we can't, then we move it back
        //    then place it on the screen
        if (!canrot) { theBlock->clockwise(); }
        placecharhlpr('p');
    }
}



// rotating to the right is the very similar to rotating to the left
void Board::rotrig() {
    if (isSameB()){
        placecharhlpr('r');
        theBlock -> clockwise();
        bool canrot = checkcharhlpr();
        if (!canrot) { theBlock ->counterclockwise(); }
        placecharhlpr('p');
    }
}



void Board::down() {
    if(ver < 14) {
        placecharhlpr('r');  //clear up all the chars
		ver ++;              //move down
        
		//try place the block, and see if we can move it
        bool mv = checkcharhlpr();
		
        //if we can't, then we move it back
		//    then place on the screen
        if (!mv){ ver --; }
        placecharhlpr('p');
        cout<<ver<<' '<<hor<<' '<<mv<<' '<<isFull[ver]<<endl;
    }
}


void Board::drop() {
	
	//move down until we can't move anymore
	int currentPos = ver;
  	down();
	while (currentPos != ver) {
  		currentPos = ver;
		down();
	}
	
    //retrieve necessary parameters
    int tall = theBlock->getHeight();
    int run = theBlock ->getWidth();
    char ** temp = theBlock -> getBlock();
    
	//link the block to the pieces
	for (int i = 0; i < tall; i ++) {
        for (int j = 0; j < run; j ++) {
            if (temp[i][j] != ' ') {
                theCoords[ver-tall+i+1][hor+j].linkBlock(theBlock);
            }
        }
    }
    
	//check if the lines are full;
	isFullfn();
	
    //theBlock->setliveCoords();
 	clearLine(ver, tall);
    
    cout << ver << tall << endl;
	theBlock = newBlock;
    ver = 3;
    hor = 0;
    bool canpl = checkcharhlpr();
    if (canpl) {
        placecharhlpr('p');
        newBlock = next->getNext();
    } else {
        theBlock = new BlockA(level);
    }
    cout << ver << ' '<< hor<<' '<<canpl<< isFull[ver]<<endl;
	
}


// reset the level, notify other components that use level
void Board::setLevel(int l) {
	level = l;
	next->notifyLevel(level);
}

void Board::levelup() { setLevel(level+1); }

void Board::leveldown() { setLevel(level-1); }



// clear the line on the board
void Board::clearLine(int startLine, int numLine) {
	
	int lineCleared = 0;
	for (int i = startLine-numLine+1; i <= startLine; i += 1) {
		if (isFull[i]) {
	        lineCleared += 1;
			for (int j = 0; j < 10; j += 1) {
				theCoords[i][j].notifyBlock();
                
                cout << "i: "<< i << " j: " << j << " AliveCoords: " << theCoords[i][j].returnNumAlive() << endl;
				if (theCoords[i][j].returnNumAlive() == 0) {
					int initialLevel = theCoords[i][j].returnLevel();
					addScore(initialLevel);
					theCoords[i][j].deleteBlock();
				}
			}
			delete [] theCoords[i];
			
			for (int k = i; k > 0 ; k -= 1) {
				theCoords[k] = theCoords[k-1];
			}
			theCoords[0] = new Coords[10];
			
			theDisplay->clearLine(i);
		}
	}
    
	if (lineCleared) {
        int scoreToAdd = (level + lineCleared) * (level + lineCleared);
        addScore(scoreToAdd);
    }

}


void Board::addScore(int toAdd) {
	score += toAdd;
	if (hiScore < score) {
		hiScore = score;
	}
}

bool Board::isSameB()
{
    //setting up all the parameters
    bool itis = true;
    int tall = theBlock->getHeight();
    int run = theBlock -> getWidth();
    char ** temp = theBlock -> getBlock();
    //now check if the current version of the block
    //can be placed at this setting
    for (int i = 0; i < tall; i++){
        for (int j = 0; j < run; j ++){
            if (temp [i][j] != ' '){
                if (theCoords[ver + i - tall + 1][hor+j].getChar() != temp[i][j]){
                    itis = false;
                }
            }
        }
    }
    return itis;
}

void Board::placecharhlpr(char cmd) {
    //getting needed parameters
    int tall = theBlock -> getHeight();
    int run = theBlock -> getWidth();
    char ** temp = theBlock -> getBlock();
    //starts checking the corresponding character location
    for (int i = 0; i < tall; i++){
        for ( int j = 0; j < run; j ++){
            if ( temp[i][j] != ' '){
                //if to put char on to the board
                if (cmd == 'p'){
                    theCoords[ver + i - tall + 1][hor+j].change(temp[i][j]);
                    theCoords[ver + i - tall + 1][hor+j].notifyDisplay(ver + i - tall + 1,hor+j, *theDisplay);
                }
                //otherwise remove char from the board
                else if (cmd == 'r') {
                    theCoords[ver + i - tall + 1][hor + j].change('_');
                    theCoords[ver + i - tall + 1][hor + j].notifyDisplay(ver + i - tall + 1,hor + j, *theDisplay);
                }
            }
        }
    }
}



bool Board::checkcharhlpr() {
    //setting up all the parameters
    bool canmv = true;
    int tall = theBlock->getHeight();
    int run = theBlock -> getWidth();
    char ** temp = theBlock -> getBlock();
    //now check if the current version of the block 
    //can be placed at this setting
    for (int i = 0; i < tall; i++){
        for (int j = 0; j < run; j ++){
            if (temp [i][j] != ' '){
                if ((theCoords[ver + i - tall + 1][hor+j].getChar() != '_') || (hor + j >= 10) || (ver + i - tall + 1 > 14)|| (hor + j < 0) || (ver+i-tall + 1 < 0)){
                    
                    cout<<theCoords[ver + i - tall + 1][hor+j].getChar()<<' '<<hor + j<<' '<<ver + i - tall + 1 <<endl;
                    canmv = false;
                }
            }
        }
    }
    return canmv;
}


void Board::isFullfn()
{
    int height = theBlock -> getHeight();
    int ctr;
    for (int i = ver; i > ver - height; i --){
        ctr = 0;
        for (int j = 0; j < 10; j ++){
            if(theCoords [i][j].getChar() != '_')
            {
                ctr ++;
            }
        }
        if (ctr == 10){
			isFull[i]=true;
        } else {
			isFull[i]=false;
		}

    }
}



std::ostream &operator<< (std::ostream &out, const Board &b) {
    out << "Level: " << b.level << endl;
	out << "Score: " << b.score << endl;
	out << "Hi Score: " << b.hiScore << endl;
	out << *b.theDisplay << endl;
	out << "Next:" << endl;
	//out << *b.newBlock;
    return out;
}
