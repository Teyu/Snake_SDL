#include "Food.h"
#include <SnakeConfig.h>

CFood::CFood() 
{ 
	isAlive = false; 
    m_Sprite.SetPos(0,0);
    size = 1;

	time_t t;
    srand( time(&t) );

    m_Sprite.Load(getDataDir() + "/cherryAtNight.bmp");
}

/**************************************************************************************************
render food
*/

void CFood::Render()
{
    m_Sprite.Render();
}

/**************************************************************************************************
set food position on screen, invalid parameters are truncated to screen borders
*/

void CFood::setPos(uint x, uint y)
{
    uint posX = x > 800 - size ? 800 - size : x;
    uint posY = y > 600 - size ? 600 - size : y;
    m_Sprite.SetPos((float) posX, (float) posY);
}

/**************************************************************************************************
set food size
*/

void CFood::setSize(uint newSize) //TODO: size can be removed
{
    size = newSize > 0 ? newSize: 1;
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
