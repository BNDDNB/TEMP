#include "nextblock.h"

using namespace std;

int main() {
 
	NextBlock *nb = NextBlock::getInstance();
	nb->setSource("sequence.txt");
	
    char cmd;
    
    while (!cin.fail()) {
        cin >> cmd;
		char block;
		switch (cmd) {
			case 'g':
				block = nb->getNextChar();
				cout << "The next block is: " << block << endl;
				break;
			case 's':
				int newSeed;
				cin >> newSeed;
				nb->setSeed(newSeed);
				break;
			case 'l':
				int newLevel;
				cin >> newLevel;
				nb->notifyLevel(newLevel);
				break;
			default:
				break;
		}
    }
}