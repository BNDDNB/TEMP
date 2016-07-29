#include <iostream>
#include <string>

#include "interpret.h"

using namespace std;

Interpret::Interpret(Board *theBoard, int level): b(theBoard), startLevel(level) {
    cout << *b << endl;
}

void Interpret::translate() {
	
    string cmd;
	cin >> cmd;
	
    int times;
    string command;
    
	while (!cin.fail()){
		unsigned int len = cmd.length();
		unsigned int i = 0;
        
        // if the first char is not a number, set # of times to 1
        if (!((cmd[i] >= '0') && (cmd[i] <= '9'))) {
            times = 1;
        // else read # of times from user input
        } else {
            times = 0;
            while ((cmd[i] >= '0') && (cmd[i] <= '9')) {
                times = times * 10 + (cmd[i]-'0');
                i += 1;
            }
        }
        
        if (i == cmd.length()) {
            cin >> cmd;
            len = cmd.length();
            i = 0;
        }
        
        // use the following letters to disdinguish commands,
        // assuming every input is valid
		char letter1, letter2, letter3, letter6;
        if (len >= i) letter1 = cmd[i];
        if (len >= i+2) letter2 = cmd[i+1];
        if (len >= i+3) letter3 = cmd[i+2];   
        if (len >= i+5) letter6 = cmd[i+5];
        
        // translate user commands
		switch (letter1) {
			case 'c':
                if (letter2 == 'o') {
					command = "countercc";
				} else if (letter2 == 'l') {
					command = "clockwise";
				}
				break;
			case 'd':
                if (letter2 == 'o') {
					command = "down";
				} else if (letter2 == 'r') {
					command = "drop";
				}
				break;
			case 'l':
				if (letter3 == 'f') {
					command = "left";
				} else if (letter3 == 'v') {
                    if (letter6 == 'u') {
						command = "levelup";
					} else if (letter6 == 'd') {
						command = "leveldown";
					}
				}
				break;
			case 'r':
                if (letter2 == 'i') {
					command = "right";
				} else if (letter2 == 'e') {
					command = "restart";
				}
				break;
			default:
				break;
		}
		
		if ((command == "restart") && (times > 1)) {
			times = 1;
		}
        
        call(times, command);
        
        cin >> cmd;
        
	}
}


void Interpret::call(const int times, const string &command) {
    for (int i = 0; i < times; i += 1) {
        if (command == "countercc") { b->rotlef(); }
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
}