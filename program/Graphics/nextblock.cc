#include "nextblock.h"

using namespace std;


// _abc_ means abc is a the name of a field / variable


// constructor
NextBlock::NextBlock(const std::string &file, const int startLevel, const int newSeed): source(NULL), fileName(file.c_str()), level(startLevel), seed(newSeed) {
    srand(seed);
    source = new ifstream(fileName);
}


// destructor
NextBlock::~NextBlock(){
    ((std::ifstream *) source)->close();
    delete source;
}


// return a char corresponding to the next Block type based on current level
// to be called by getNext()
char NextBlock::getNextChar() {
    char next;
	int blockIndex;
    switch (level) {
        case 0:
			if (source->eof()) {
				((std::ifstream *) source)->close();
				delete source;
				source = new ifstream(fileName);
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
    }
    
    return next;

}


// get a pointer to a new block according to the result of getNextChar()
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


// to be called by Board: update _level_
void NextBlock::notifyLevel(int l) {
    level = l;
}


// to be called by Board: reset _source_, _seed_ and _level_
void NextBlock::restart() {
	
    // reset _seed_
    srand(seed);
    
    // reset input stream
    ((std::ifstream *) source)->close();
    delete source;
    source = new ifstream(fileName);
}