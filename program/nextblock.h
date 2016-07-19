#ifndef __NEXTBLOCK_H__
#define __NEXTBLOCK_H__

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "block.h"

class NextBlock {
	
	char getNextChar();
	
	std::istream *source;
	std::string fileName;
    int level;
    int seed;

public:

	NextBlock();
	~NextBlock();
	Block *getNext();
    void setSource(const std::string &file);
    void setSeed(int seed);
    void notifyLevel(int l);
	void restart();
};

#endif
