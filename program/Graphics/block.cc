#include "block.h"
#include <iostream>
using namespace std;

Block::Block(){}

//based on the preset number, get the block pattern
char ** Block::getBlock() const
{
    switch (setnum)
    {
        case 0:
            return preset1;
        case 1:
            return preset2;
        case 2:
            return preset3;
        case 3:
            return preset4;
        default:
            return NULL;
    }
}

//rotate - next patern
void Block::counterclockwise()
{
    if(setnum == 3)
    {
        setnum = 0;
    }
    else
    {
        setnum++;
    }
    
    
    int temp = width;
    width = height;
    height = temp;

}

//rotate - previous pattern
void Block::clockwise()
{
    if(setnum == 0)
    {
        setnum = 3;
    }
    else
    {
        setnum --;
    }
    
    int temp = width;
    width = height;
    height = temp;
    
}

//one of the component is deleted
void Block::notify() {
	liveCoords -= 1;
}

//destructor
Block::~Block()
{
    int maxi = width > height? width:height;
    for (int i = 0; i < maxi; i++)
    {
        delete [] preset1[i];
        delete [] preset2[i];
        delete [] preset3[i];
        delete [] preset4[i];
    }
    delete [] preset1;
    delete [] preset2;
    delete [] preset3;
    delete [] preset4;
}

//accessors
int Block::getHeight()
{
    return height;
}

int Block::getWidth()
{
    return width;
}

int Block::getlvl()
{
    return level;
}

int Block::getliveCoords()
{
    return liveCoords;
}

//friend for printing
std::ostream &operator<< (std::ostream &out, const Block &b) {
    char ** temp = b.preset1;
    for(int i = 0; i <b.height; i++)
    {
        for (int j = 0; j < b.width; j ++)
        {
            out<<temp[i][j];
        }
        if(i != b.height - 1)
        {
            out << endl;
        }
    }
    return out;
}

//below are the initialization of different subclasses
//all initializations uses same idea.

BlockS::BlockS(int lvl)
{
    width = 3;          //width of this block's setting
    height = 2;         //height
    level = lvl;        //what level was this block created
    setnum = 0;         //default value
    liveCoords= 4;      //4 componengt
        preset1 = new char * [3];   //left turn 0
        preset2 = new char * [3];   //left turn once
        preset3 = new char * [3];   //left turn twice
        preset4 = new char * [3];   //left turn 3 times
        for (int i = 0; i< 3; i++)
        {//initializing preset
            preset1 [i] = new char[3];
            preset2 [i] = new char[3];
            preset3 [i] = new char[3];
            preset4 [i] = new char[3];
            for (int j = 0; j < 3; j++)
            {
                preset1[i][j] = ' ';
                preset2[i][j] = ' ';
                preset3[i][j] = ' ';
                preset4[i][j] = ' ';
            }
        }
    //starts mapping out what the block look like
        preset1[1][0]=preset1[1][1]=preset1[0][1]=preset1[0][2]= 'S';
        preset2[0][0]= preset2[1][0] = preset2[1][1] = preset2[2][1] = 'S';
        preset3[1][0]=preset3[1][1]=preset3[0][1]=preset3[0][2]='S';
        preset4[0][0] = preset4[1][0]=preset4[1][1]=preset4[2][1]='S';
}

BlockI::BlockI(int lvl)
{
    width = 4;
    height = 1;
    level = lvl;
    setnum = 0;
    liveCoords= 4;
    
        preset1 = new char * [4];   //left turn 0
        preset2 = new char * [4];   //left turn once
        preset3 = new char * [4];   //left turn twice
        preset4 = new char * [4];   //left turn 3 times
        for (int i = 0; i< 4; i++)
        {
            preset1 [i] = new char[4];
            preset2 [i] = new char[4];
            preset3 [i] = new char[4];
            preset4 [i] = new char[4];
            for (int j = 0; j < 4; j++)
            {
                preset1[i][j] = ' ';
                preset2[i][j] = ' ';
                preset3[i][j] = ' ';
                preset4[i][j] = ' ';
            }
        }
        preset1[0][0]=preset1[0][1]=preset1[0][2]=preset1[0][3]= 'I';
        preset2[0][0]= preset2[1][0] = preset2[2][0] = preset2[3][0] = 'I';
        preset3[0][0]=preset3[0][1]=preset3[0][2]=preset3[0][3]='I';
        preset4[0][0] = preset4[1][0]=preset4[2][0]=preset4[3][0]='I';
}

BlockT::BlockT(int lvl)
{
    width = 3;
    height = 2;
    level = lvl;
    setnum = 0;
    liveCoords= 4;
        preset1 = new char * [3];   //left turn 0
        preset2 = new char * [3];   //left turn once
        preset3 = new char * [3];   //left turn twice
        preset4 = new char * [3];   //left turn 3 times
        for (int i = 0; i< 3; i++)
        {
            preset1 [i] = new char[3];
            preset2 [i] = new char[3];
            preset3 [i] = new char[3];
            preset4 [i] = new char[3];
            for (int j = 0; j < 3; j++)
            {
                preset1[i][j] = ' ';
                preset2[i][j] = ' ';
                preset3[i][j] = ' ';
                preset4[i][j] = ' ';
            }
        }
        preset1[0][0]=preset1[0][1]=preset1[0][2]=preset1[1][1]= 'T';
        preset2[0][0]= preset2[1][0] = preset2[2][0] = preset2[1][1] = 'T';
        preset3[1][0]=preset3[1][1]=preset3[1][2]=preset3[0][1]='T';
        preset4[1][0] = preset4[0][1]=preset4[2][1]=preset4[1][1]='T';
}

BlockJ::BlockJ(int lvl)
{
    width = 3;
    height = 2;
    level = lvl;
    setnum = 0;
    liveCoords= 4;
        preset1 = new char * [3];   //left turn 0
        preset2 = new char * [3];   //left turn once
        preset3 = new char * [3];   //left turn twice
        preset4 = new char * [3];   //left turn 3 times
        for (int i = 0; i< 3; i++)
        {
            preset1 [i] = new char[3];
            preset2 [i] = new char[3];
            preset3 [i] = new char[3];
            preset4 [i] = new char[3];
            for (int j = 0; j < 3; j++)
            {
                preset1[i][j] = ' ';
                preset2[i][j] = ' ';
                preset3[i][j] = ' ';
                preset4[i][j] = ' ';
            }
        }
        preset1[0][0]=preset1[1][0]=preset1[1][2]=preset1[1][1]= 'J';
        preset2[2][0]= preset2[0][1] = preset2[2][1] = preset2[1][1] = 'J';
        preset3[0][0]=preset3[1][2]=preset3[0][2]=preset3[0][1]='J';
        preset4[0][0] = preset4[1][0]=preset4[2][0]=preset4[0][1]='J';
}

BlockL::BlockL(int lvl)
{
    width = 3;
    height = 2;
    level = lvl;
    setnum = 0;
    liveCoords= 4;
        preset1 = new char * [3];   //left turn 0
        preset2 = new char * [3];   //left turn once
        preset3 = new char * [3];   //left turn twice
        preset4 = new char * [3];   //left turn 3 times
        for (int i = 0; i< 3; i++)
        {
            preset1 [i] = new char[3];
            preset2 [i] = new char[3];
            preset3 [i] = new char[3];
            preset4 [i] = new char[3];
            for (int j = 0; j < 3; j++)
            {
                preset1[i][j] = ' ';
                preset2[i][j] = ' ';
                preset3[i][j] = ' ';
                preset4[i][j] = ' ';
            }
        }
        preset1[0][2]=preset1[1][0]=preset1[1][2]=preset1[1][1]= 'L';
        preset2[0][0]= preset2[0][1] = preset2[1][1] = preset2[2][1] = 'L';
        preset3[0][0]=preset3[1][0]=preset3[0][2]=preset3[0][1]='L';
        preset4[0][0] = preset4[1][0]=preset4[2][0]=preset4[2][1]='L';
}

BlockO::BlockO(int lvl)
{
    width = 2;
    height = 2;
    level = lvl;
    setnum = 0;
    liveCoords= 4;
        preset1 = new char * [2];   //left turn 0
        preset2 = new char * [2];   //left turn once
        preset3 = new char * [2];   //left turn twice
        preset4 = new char * [2];   //left turn 3 times
        for (int i = 0; i< 2; i++)
        {
            preset1 [i] = new char[2];
            preset2 [i] = new char[2];
            preset3 [i] = new char[2];
            preset4 [i] = new char[2];
            for (int j = 0; j < 2; j++)
            {
                preset1[i][j] = ' ';
                preset2[i][j] = ' ';
                preset3[i][j] = ' ';
                preset4[i][j] = ' ';
            }
        }
        preset1[0][0]=preset1[1][0]=preset1[1][1]=preset1[0][1]= 'O';
        preset2[0][0]=preset2[1][0]=preset2[1][1]=preset2[0][1]= 'O';
        preset3[0][0]=preset3[1][0]=preset3[1][1]=preset3[0][1]= 'O';
        preset4[0][0]=preset4[1][0]=preset4[1][1]=preset4[0][1]= 'O';      
}

BlockZ::BlockZ(int lvl)
{
    width = 3;
    height = 2;
    level = lvl;
    setnum = 0;
    liveCoords= 4;
        preset1 = new char * [3];   //left turn 0
        preset2 = new char * [3];   //left turn once
        preset3 = new char * [3];   //left turn twice
        preset4 = new char * [3];   //left turn 3 times
        for (int i = 0; i< 3; i++)
        {
            preset1 [i] = new char[3];
            preset2 [i] = new char[3];
            preset3 [i] = new char[3];
            preset4 [i] = new char[3];
            for (int j = 0; j < 3; j++)
            {
                preset1[i][j] = ' ';
                preset2[i][j] = ' ';
                preset3[i][j] = ' ';
                preset4[i][j] = ' ';
            }
        }
        preset1[0][0]=preset1[1][1]=preset1[0][1]=preset1[1][2]= 'Z';
        preset2[0][1]=preset2[1][0]=preset2[1][1]=preset2[2][0]= 'Z';
        preset3[0][0]=preset3[1][1]=preset3[0][1]=preset3[1][2]= 'Z';
        preset4[0][1]=preset4[1][0]=preset4[1][1]=preset4[2][0]= 'Z';
}