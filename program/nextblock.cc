#include "nextblock.h"

using namespace std;

NextBlock::NextBlock(): source(NULL), fileName(""), level(0), seed(1) {}

NextBlock::~NextBlock(){
	if (fileName != "") {
		((std::ifstream *) source)->close();
		delete source;
	}
}

char NextBlock::getNextChar() {
    char next;
	int blockIndex;
    switch (level) {
        case 0:
			if (source->eof()) {
				((std::ifstream *) source)->close();
				delete source;
				source = new ifstream(fileName.c_str());
			} else {
				(*source) >> next;
				while ((next < 'A') || (next > 'Z')) {
					next = getNextChar();
				}
            }
			break;
		case 1:
			blockIndex = rand() % 6;
			switch (blockIndex) {
				case 0: next = 'I'; break;
                case 1: next = 'J'; break;
                case 2: next = 'L'; break;
                case 3: next = 'O'; break;
				case 4: next = 'T'; break;
				case 5: 
					if (rand() % 2) next = 'S';
					else next = 'Z';	
				break;
			}
        case 2:
            blockIndex = rand() % 7;
            switch (blockIndex) {
                case 0: next = 'I'; break;
                case 1: next = 'J'; break;
                case 2: next = 'L'; break;
                case 3: next = 'O'; break;
				case 4: next = 'T'; break;
                case 5: next = 'S'; break;
                case 6: next = 'Z'; break;
                
            }
        case 3:
            blockIndex = rand() % 9;
            switch (blockIndex) {
                case 0: next = 'I'; break;
                case 1: next = 'J'; break;
                case 2: next = 'L'; break;
                case 3: next = 'O'; break;
                case 4: next = 'T'; break;
                case 5: next = 'S'; break;
                case 6: next = 'Z'; break;
                case 7: next = 'S'; break;
                case 8: next = 'Z'; break;
            }
        default:
            break;
    }
    
	return next;
}

Block *NextBlock::getNext() {
	
	char next = getNextChar();
	Block *newBlock;
	
	switch (next) {
		case 'I': newBlock = new BlockI(level); break;
		case 'J': newBlock = new BlockJ(level); break;
		case 'L': newBlock = new BlockL(level); break;
		case 'O': newBlock = new BlockO(level); break;
		case 'T': newBlock = new BlockT(level); break;
		case 'S': newBlock = new BlockS(level); break;
		case 'Z': newBlock = new BlockZ(level); break;
	}
	return newBlock;
}

void NextBlock::setSource(const string &file) {
	fileName = file;
	source = new ifstream(fileName.c_str());
}

void NextBlock::setSeed(int newSeed) {
    seed = newSeed;
    srand(seed);
}

void NextBlock::notifyLevel(int l) {
    level = l;
}

void NextBlock::restart() {
	
    setSeed(seed);
    
    if (fileName != "") {
		((std::ifstream *) source)->close();
		delete source;
		source = new ifstream(fileName.c_str());
	}
}
	
