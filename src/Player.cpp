#include "Player.h"

/**************************************************************************************************
initializes member variables
*/

void CPlayer::Init(int KeyL, int KeyR, int startPosX, int startPosY, direction startDir, int res)
{
    KeyLock = false;
    growLock = false;
	Points = 0;
	length = 0;
	KeyLeft = KeyL;
	KeyRight = KeyR;

    int startLength = 5;
    init(startPosX, startPosY, startLength, res, startDir); //TODO: rename Init and explicitly call CSnake::Init (parameter sollten nicht notwendig sein)
}

/**************************************************************************************************
checks keyboard input and updates direction of snake
*/

void CPlayer::Update()
{

    if (KI == false) // TODO: remove wenn CBot implementiert
    {
        m_pFramework->Update();

        if (!KeyLock)
        {
            if (m_pFramework->KeyDown(KeyRight))
            {
                changeDirection(KeyRight);
            }
            if (m_pFramework->KeyDown(KeyLeft))
            {
                changeDirection(KeyLeft);
            }
            KeyLock = true;
        }
        if ((!m_pFramework->KeyDown(KeyRight)) && (!m_pFramework->KeyDown(KeyLeft)))
        {
            KeyLock = false;
        }
    }
}

/**************************************************************************************************
let Snake grow and gain points
*/

void CPlayer::growSnake()
{ 
	Points++;
	grow();
}
