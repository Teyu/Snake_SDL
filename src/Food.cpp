#include "Food.h"

CFood::CFood() 
{ 
	isAlive = false; 
	Pos.x = 0; 
	Pos.y = 0; 
    Pos.w = 1;
    Pos.h = 1;
    size = 1;

	time_t t;
    srand( time(&t) );
}

/**************************************************************************************************
set food position on screen, invalid parameters are truncated to screen borders
*/

void CFood::setPos(uint x, uint y)
{
    Pos.x = x > 800 - size ? 800 - size : x;
    Pos.y = y > 600 - size ? 600 - size : y;
}

/**************************************************************************************************
set food size
*/

void CFood::setSize(uint newSize)
{
    size = newSize > 0 ? newSize: 1;
	Pos.h = size;
	Pos.w = size;
}

/**************************************************************************************************
generates a random position, if food is not alive. Returns true if new food has been generated, otherwise false
*/

bool CFood::spawn()
{
    if (!isAlive)
    {
        int Posx = (rand() % (800/size - 1))*size ;
        int Posy = (rand() % (600/size - 1))*size ;

        setPos(Posx, Posy);

        isAlive = true;

        return true;
	}

    return false;
}
