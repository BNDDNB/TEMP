#ifndef __INTERPRET_H__
#define __INTERPRET_H__

#include "board.h"


// _abc_ means abc is a the name of a field / variable


// class Interpret: read user input, interpret it and call corresponding functions in Board

class Interpret {

	Board *b;			 // pointer to the game controller Board
    int startLevel;		 // store the initial level; used when the game restarted
	std::string command; // store the text command passed in; will be translated later
    int times;			 // store number of times a command is called
    bool matched;		 // indicate if a user input is matched with a valid command
	
	// private method, verify if the command should be interpreted as the target string
    void verify(unsigned const int minLen, unsigned const int cmdLen, const std::string &target);
	
	// private method, execute the corresponding function of b according to our command
	void call();
	
public:
    
	Interpret(Board *theBoard, int level);  // constructor
	~Interpret();							// destructor
	
	// public method,read user commands, translate them and call Interpret::call()
	void translate();						
};


#endif