#include <iostream>
#include <string>

#include "interpret.h"

using namespace std;


// _abc_ means abc is a the name of a field / variable


// constructor
Interpret::Interpret(Board *theBoard, int level):
    b(theBoard), startLevel(level), command(""), times(0),  matched(false) {
}


// destructor
Interpret::~Interpret() {
	delete b;
}


// call the command corresbonding to _command_ _times_ times in Board 
void Interpret::call() {
    for (int i = 0; i < times; i += 1) {
        if (command == "counterclockwise") { b->rotlef(); }
        else if (command == "clockwise") { b->rotrig(); }
        else if (command == "down") { b->down(); }
        else if (command == "drop") { b->drop(); }
        else if (command == "left") { b->left(); }
        else if (command == "levelup") { b->levelup(); }
        else if (command == "leveldown") { b->leveldown(); }
        else if (command == "right") { b->right(); }
        else if (command == "restart") { b->restart(startLevel); }
    }
	cout << *b << endl;
	
	// if _command_ is not matched, output an error message
    if (!matched) cerr << "Invalid input :(" << endl;
    
}


// verify that the command from input can be matched with target
//		minLen: the minimum # of chars required to identify target command with others
//		cmdLen: the # of chars in _command_
//		target: the target that we want to match _command_ with
void Interpret::verify(unsigned const int minLen, unsigned const int cmdLen, const std::string &target) {
    // if _command_ is matched previously, or the length of _command_ is less than 
	//		the minumum length to identify _target_ from other commands, do nothing
	// else compare the two commands char by char
	if ((matched) || (cmdLen < minLen)) {
		return;
    } else {
        unsigned int i = 1;
        unsigned int targetLen = target.length();
		// stop the loop if _command_ and _target_ are different
        while (command[i-1] == target[i-1]) {
            // if end of _command_ is reached,
			//		set command to target, change matched to true;
			// else if the end of _target_ is reached, do nothing;
			// else increase index, compare the next char.
			if (i == cmdLen) {
                command = target;
                matched = true;
                return;
			} else if (i == targetLen) {
                return;
			} else {
                i += 1;
            }
        }
        return;
    }    
}


// read in commands from cin and traslate it
// then call Interpret::call() to execute the translated _command_ in Board
void Interpret::translate() {

    string cmd;
	cin >> cmd;
    
	while (!cin.fail()){
        
		unsigned int len = cmd.length();
		unsigned int i = 0;
        
        // if the first char is not a multiplier, set # of times to 1
        if (!((cmd[i] >= '0') && (cmd[i] <= '9'))) {
            times = 1;
        // else read the multiplier from user input
        } else {
            times = 0;
            while ((cmd[i] >= '0') && (cmd[i] <= '9')) {
                times = times * 10 + (cmd[i]-'0');
                i += 1;
            }
        }
        
        // if the input is only a number, read another string from cin
		if (i == cmd.length()) {
            cin >> cmd;
            len = cmd.length();
            i = 0;
        }
        
		// _command_: the text command, e.g., if "34ri" is read, command = "ri"
        command = cmd.substr(i,len);
        
        // verify if _command_ can be matched with one of the following commands
		verify(2, len-i, "counterclockwise");
        verify(2, len-i, "clockwise");
        verify(2, len-i, "down");
        verify(2, len-i, "drop");
		verify(3, len-i, "left");
		verify(6, len-i, "levelup");
		verify(6, len-i, "leveldown");
        verify(2, len-i, "right");
        verify(2, len-i, "restart");
		
        // if _command_ is not matched, don't call anything in Board
		if (!matched) {
            times = 0;
		// if the command is restart, ignore the multiplier (including 0)
		} else if (command == "restart") {
			times = 1;
		}
        
		// call _command_ _times_ time
        call();
    
		// set _matched_ to false; read another input from cin
        matched = false;
        cin >> cmd;
        
	}
}