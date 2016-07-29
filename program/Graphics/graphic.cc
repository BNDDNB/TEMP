#include <sstream>

#include "graphic.h"

using namespace std;


// constructor
Graphic::Graphic(TextDisplay *theDis): d(theDis), w(NULL) {}


// destructor
Graphic::~Graphic() {
    if (w != NULL) {
        delete w;
    }
}


// choose the color code according to block type _type_
int Graphic::chooseColor(char type) const{
    int colourCode;
    switch (type) {
        case ' ': colourCode = 0; break;
        case 'I': colourCode = 2; break;
        case 'J': colourCode = 3; break;
        case 'L': colourCode = 4; break;
        case 'O': colourCode = 5; break;
        case 'S': colourCode = 7; break;
        case 'T': colourCode = 8; break;
        case 'Z': colourCode = 9; break;
            
    }
    return colourCode;
}


// private method: convert int to string (for printing numbers)
string Graphic::int_to_str(const int& theInt) const{
    stringstream ss;
    ss << theInt;
    return ss.str();
}


// initializing the graphic component
void Graphic::init(int lvl, int scr, int hiScr) {
    w = new Xwindow(340,490);
    w->drawString(5, 15, "Level: " + int_to_str(lvl));
    w->drawString(5, 30, "Score: " + int_to_str(scr));
    w->drawString(5, 45, "Hi Score: " + int_to_str(hiScr));
    w->fillRectangle(60, 55, 220, 3, 1);
    w->fillRectangle(60, 395, 220, 3, 1);
    w->drawString(5, 410, "Next: ");
    
    for (int i = 2; i < 4; i += 1) {
        for (int j = 0; j < 10; j += 1) {
            notify(i, j, d->theTextDisplay[i][j]);
        }
    }
}


// to be called by Board: restart the display of Board ONLY 
void Graphic::restart() {
    if (w != NULL) {
		
		// draw a large white rectangle
		w->fillRectangle(60, 60, 220, 330, 0);
    
	// place the block on the scree according to text display
    for (int i = 2; i < 4; i += 1) {
        for (int j = 0; j < 4; j += 1) {
            notify(i, j, d->theTextDisplay[i][j]);
			}
		}
	}
}

// to be called by Board: update _lvl_
void Graphic::notifyLevel(int lvl) {
    if (w != NULL) {
    w->fillRectangle(5, 0, 200, 15, 0);
    w->drawString(5, 15, "Level: " + int_to_str(lvl));
    }
}


// to be called by Board: update _scr_ and _hiScr_
void Graphic::notifyScore(int scr, int hiScr) {
    if (w != NULL) {
        w->fillRectangle(5, 15, 200, 30, 0);
        w->drawString(5, 30, "Score: " + int_to_str(scr));
        w->drawString(5, 45, "Hi Score: " + int_to_str(hiScr));
    }
}


// to be called by Board to update the graphic of the board which
// corresponds to the Coords at row _x_ col _y_ with type char _type_
void Graphic::notify(int x, int y, char type) {
    if (w != NULL) {
    w->fillRectangle(y*22+60, x*22+60, 21, 21, chooseColor(type));
    }
}


// to be called by Board to update the graphic of next block which corresponds
// to the char at row _x_ col _y_ of the block pattern, with type _type_
void Graphic::notifyNext(int x, int y, char type) {
    if (w != NULL) {
        w->fillRectangle(y*22+60, x*22+420, 21, 21, chooseColor(type));
    }
}


// to be called by Board to clear the line _lineNum_
// redraw all the lines above (including) _lineNum_ according to text display
void Graphic::clearLine(int lineNum) {
    if (w != NULL) {
        for (int i = lineNum; i >= 0; i -= 1) {
            for (int j = 0; j < 10; j += 1) {
                notify(i, j, d->theTextDisplay[i][j]);
            }
        }
    }
}