#ifndef ____Block__
#define ____Block__

#include <iostream>

class Block {
protected:
    char ** preset1;    //normal Block
    char ** preset2;    //left rotate once
    char ** preset3;    //twice
    char ** preset4;    //three times
    int width, height;   
    int level;  //this stores the leve the Block is generated
    int setnum;
	int liveCoords;
public:
    Block();
	void clockwise();   //decrease setnumber by 1
	void counterclockwise();    //increase setnumber by 1;
    int getoriver();    //verticle axis accessor
    int getorihor();    //horizontal axis accessor
    int getHeight();    //height accessor
    int getWidth();     //Width accessor
    int getlvl();       //level accessor
    int getliveCoords();    //accessor to liveCoords field
    char ** getBlock() const; //preset pattern accessor
	void notify();      //being notified to update liveCoords
	~Block();           //block deallocation
    friend std::ostream &operator<<(std::ostream &out, const Block &td);
};

//class sBlock inherited from Block
class BlockS:public Block{
public:
    BlockS(int lvl);
};

class BlockI:public Block{
public:
    BlockI(int lvl);
};

class BlockT:public Block{
public:
    BlockT(int lvl);
};

class BlockJ:public Block{
public:
    BlockJ(int lvl);
};

class BlockL:public Block{
public:
    BlockL(int lvl);
};

class BlockO:public Block{
public:
    BlockO(int lvl);
};

class BlockZ:public Block{
public:
    BlockZ(int lvl);
};

class BlockA:public Block{
public:
    BlockA(int lvl);
};

#endif /* defined(____Block__) */
