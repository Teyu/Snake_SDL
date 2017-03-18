#include "Tastatur.h"

CTastatur::CTastatur()
{
    m_pKeystate = SDL_GetKeyState (NULL);
}

void CTastatur::update()
{
	timer.update();
    SDL_PumpEvents();
}

bool CTastatur::KeyDown( int Key_ID)
{
	return (m_pKeystate[Key_ID] ? true:false);
}

