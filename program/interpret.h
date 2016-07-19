#ifndef ____INTERPRET_H____
#define ____INTERPRET_H____

#include "board.h"

class Interpret {
	Board *b;
	int startLevel;
	
public:
	Interpret(Board *theBoard, int level);
	void translate();
	void call(const int times, const std::string &command);
};

#endif