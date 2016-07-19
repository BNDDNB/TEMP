#include "board.h"
#include "nextblock.h"
#include "interpret.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
	
	bool graphical = true;
	int seed = 0;
	int startlevel = 0;
	string scriptfile = "sequence.txt";
	
	for (int i = 1; i < argc; i += 1) {
	   if (!strcmp(argv[i], "-text")) {
		   graphical = false;
	   } else if (!strcmp(argv[i], "-seed")) {
		   seed = atoi(argv[++i]);
	   } else if (!strcmp(argv[i], "-scriptfile")) {
		   scriptfile = argv[++i];
	   } else if (!strcmp(argv[i], "-startlevel")) {
		   startlevel = atoi(argv[++i]);
	   }
	}
	
	NextBlock *next = new NextBlock();
	next->setSource(scriptfile);
	if (seed) next->setSeed(seed);
	if (startlevel) next->notifyLevel(startlevel);
	
	Board *theBoard = new Board(startlevel, next);
	//if (graphical) theBoard->setGraphic();
	
	Interpret *interpreter = new Interpret(theBoard, startlevel);
	interpreter->translate();
    
    delete interpreter;
    delete theBoard;
    delete next;
	
}