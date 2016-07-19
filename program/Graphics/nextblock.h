#ifndef __NEXTBLOCK_H__
#define __NEXTBLOCK_H__

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "block.h"


// _abc_ means abc is a the name of a field / variable


// class NextBlock: generate new blocks

class NextBlock {
	
	std::istream *source;   // store the source
	const char *fileName;   // store the filename
    int level;              // store the current level
    const int seed;         // store the seed
    
    // private method, return a char corresponding to the next Block type
    // to be called by getNext()
    char getNextChar();
	

public:

    // constructor and destructor
	NextBlock(const std::string &file, const int startLevel, const int newSeed); 
    ~NextBlock();
    
    // public method, return a pointer to the next Block
	Block *getNext();
    
    // to be called by Board: update _level_
    void notifyLevel(int l);
	
    // to be called by Board: reset _source_, _seed_ and _level_
    void restart();
};

#endif