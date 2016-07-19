#include <iostream>
#include <cstring>
#include <cstdlib>

#include "board.h"
#include "nextblock.h"
#include "interpret.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	// default options
	bool graphical = true;
	int seed = 1;
	int startlevel = 0;
	string scriptfile = "sequence.txt";
	
	// read the list of arguments passed from the terminal
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
	
	// initialize the factory of Blocks (NextBlock)
	NextBlock *next = new NextBlock(scriptfile, startlevel, seed);
	
	// initialize the game controller (Board) and print it
	// turn on the graphics if the user did not enter -text
	Board *theBoard = new Board(startlevel, next);
	cout << *theBoard << endl;
	if (graphical) theBoard->setGraphic();
	
	// initialize the command interpreter (Interpret)
	// start reading user commands by calling the method translate()
	Interpret *interpreter = new Interpret(theBoard, startlevel);
	interpreter->translate();
    
    delete interpreter;
	
}