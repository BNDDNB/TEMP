#include "board.h"
#include <iostream>
using namespace std;



Board::Board(int presetlevel, NextBlock *nextb) {
    //initialize board
    theCoords = new Coords *[15];
    for (int i = 0; i < 15; i++) {
        theCoords[i] = new Coords[10];
    }
    gameOver = true;
    //get NextBlock, generate desired blocks
    next = nextb;
    theDisplay = new TextDisplay();
    theBlock = next->getNext();
	newBlock = next->getNext();
    
    //setting up current location, level, scores etc.
    level = presetlevel;
    score = hiScore = 0;
    ver = 3;
    hor = 0;
    
    theGraphic = new Graphic(theDisplay);
    
    for (int i = 0; i < 15; i++) {
        isFull[i] = false;
    }

    //put the current block on the board
    placecharhlpr('p');

}

Board::~Board() {
	for (int i = 0; i < 15; i++) {
        //deleting coordinate
        for (int j = 0; j < 10; j += 1) {
            theCoords[i][j].notifyBlock();
            if (!theCoords[i][j].returnNumAlive()) {
                theCoords[i][j].deleteBlock();
            }
        }
        delete [] theCoords[i];
    }
	delete [] theCoords;
    //deleting other component
	delete theDisplay;
    delete theGraphic;
    delete next;
    //prevent double delete
    if (theBlock == newBlock) {
        delete theBlock;
        newBlock = NULL;
    } else {
        delete theBlock;
        delete newBlock;
    }
}

void Board::setGraphic () {
    //initializing graphics
    theGraphic->init(level, score, hiScore);
    NextBlockGraph('p');
}


void Board::restart(int startLevel) {
	for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j += 1) {
            //remaking the coordinate
            theCoords[i][j].notifyBlock();
            if (!theCoords[i][j].returnNumAlive()) {
                theCoords[i][j].deleteBlock();
            }
        }
        delete [] theCoords[i];
    }
	delete [] theCoords;
    //remove previously left next block
    NextBlockGraph('r');
    //prevent double delete
    if (theBlock == newBlock) {
        delete newBlock;
        theBlock = NULL;
    } else {
        delete theBlock;
        delete newBlock;
    }
	//remaking coordinate
	theCoords= new Coords *[15];
    for (int i = 0; i < 15; i++) {
        theCoords[i] = new Coords [10];
    }
    //setting up parameters
	setLevel(startLevel);
    next->restart();
	theBlock = next->getNext();
	newBlock = next->getNext();
    
	ver = 3;
    hor = 0;
	score = 0;
	
    
	for (int i = 0; i < 15; i++) {
        isFull[i] = false;
    }
    
    gameOver = true;
	theDisplay->clear();
    placecharhlpr('p');
    theGraphic->restart();
    NextBlockGraph('p');
    theGraphic->notifyScore(score, hiScore);
}



void Board::left() {
    if(hor > 0 && isSameB() && gameOver){
		placecharhlpr('r');  //clear up all chars
        hor --;              //movev to the left
		
		//try to place the block, and see if we can move it
        bool mv = checkcharhlpr();
		
        //if we can't, then we move it back
		//    then place it on the screen
        if (!mv) { hor ++; }
        placecharhlpr('p');
    }
}



// moving to the right is the very similar to moving to the left
void Board::right() {
    if(hor < 9 && isSameB() && gameOver){
        placecharhlpr('r');  
        hor ++;
		bool mv = checkcharhlpr();
        if (!mv) { hor --; }
        placecharhlpr('p');
    }
}



void Board::rotlef() {
    if (isSameB() && gameOver){
        placecharhlpr('r');           //clear up all chars
        theBlock->counterclockwise(); //rotate the block
        //try to place the block to see if we can rotate it
        bool canrot = checkcharhlpr();
        //if we can't, move it back
        //    then place it on the screen
        if (!canrot) { theBlock->clockwise(); }
        placecharhlpr('p');
    }
}



// rotating to the right is the very similar to rotating to the left
void Board::rotrig() {
    if (isSameB() && gameOver){
        //remove -> move -> check -> place
        placecharhlpr('r');
        theBlock -> clockwise();
        bool canrot = checkcharhlpr();
        if (!canrot) { theBlock ->counterclockwise(); }
        placecharhlpr('p');
    }
}



void Board::down() {
    if(ver < 14 && isSameB() && gameOver) {
        placecharhlpr('r');  //clear up all the chars
		ver ++;              //move down
        
		//try place the block, and see if we can move it
        bool mv = checkcharhlpr();
		
        //if we can't, then we move it back
		//    then place on the screen
        if (!mv){ ver --; }
        placecharhlpr('p');
    }
}


void Board::drop() {
	
    if (theBlock == newBlock) {
        return;
    }
    
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

	theBlock = newBlock;
    ver = 3;
    hor = 0;
    bool canpl = checkcharhlpr();
    if (canpl) {
        placecharhlpr('p');
        NextBlockGraph('r');
        newBlock = next->getNext();
        NextBlockGraph('p');
    } else {
        gameOver = false;
    }
}


// reset the level, notify other components that use level
void Board::setLevel(int l) {
	if(l > 3){
        level = 3;
    }else if (l < 0){
        level = 0;
    }else{
        level = l;   
    }
	next->notifyLevel(level);
    theGraphic->notifyLevel(level);
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
    
    theGraphic->clearLine(startLine);
    
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
    theGraphic->notifyScore(score, hiScore);
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
                int row = ver + i - tall + 1;
                int col = hor + j;
                if (cmd == 'p'){
                    theCoords[row][col].change(temp[i][j]);
                    theCoords[row][col].notifyDisplay(row, col, *theDisplay);
                    theCoords[row][col].notifyGraphic(row, col, *theGraphic);
                }
                //otherwise remove char from the board
                else if (cmd == 'r') {
                    theCoords[row][col].change(' ');
                    theCoords[row][col].notifyDisplay(row, col, *theDisplay);
                    theCoords[row][col].notifyGraphic(row, col, *theGraphic);
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
    //check if the current version of the block 
    //can be placed at this setting
    for (int i = 0; i < tall; i++){
        for (int j = 0; j < run; j ++){
            if (temp [i][j] != ' '){
                if((hor + j >= 10) || (ver + i - tall + 1 > 14)|| (hor + j < 0) || (ver+i-tall + 1 < 0)){
                    canmv = false;
                }else if (theCoords[ver + i - tall + 1][hor+j].getChar() != ' '){
                    canmv = false;
                }
            }
        }
    }
    return canmv;
}

void Board::NextBlockGraph(char cmd){
    //retrieve parameters from next block
    int tall = newBlock -> getHeight();
    int run = newBlock -> getWidth();
    char ** temp = newBlock -> getBlock();
    for (int i = 0; i < tall; i ++){
        for (int j = 0; j< run; j++) {
            //depending on requirment either remove or place
            if(temp[i][j] != 0){
                if (cmd == 'p'){
                    theGraphic -> notifyNext(i,j,temp[i][j]);
                } else if (cmd == 'r'){
                    theGraphic -> notifyNext(i,j, ' ');
                }
            }
        }
    }
}

//this function checks if a row of coordinate is full
void Board::isFullfn()
{
    int height = theBlock -> getHeight();
    int ctr;
    for (int i = ver; i > ver - height; i --){
        ctr = 0;
        for (int j = 0; j < 10; j ++){
            if(theCoords [i][j].getChar() != ' ')
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


//printing board
std::ostream &operator<< (std::ostream &out, const Board &b) {
    
        out << "Level: " << b.level << endl;
        out << "Score: " << b.score << endl;
        out << "Hi Score: " << b.hiScore << endl;
        out << *b.theDisplay << endl;
        out << "Next:" << endl;
        out << *b.newBlock;
    if(!b.gameOver){
        out<<endl<<"No more moves, please restart!";
    }
    return out;
}
