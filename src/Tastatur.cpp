#include "Tastatur.h"

//Konstruktor:
CTastatur::CTastatur()
{
	m_pKeystate = SDL_GetKeyState (NULL); //Gibt einen Zeiger auf ein SDL internes Array zur�ck,
			// das den aktuellen Tastaturstatus widerspiegelt
}

//Update:
void CTastatur::update()
{
	timer.update();
	SDL_PumpEvents(); //Das interne Array (s.o.) wird aktualisiert
}

//KeyDown
bool CTastatur::KeyDown( int Key_ID)
{
	//Tastaturabfrage:
	//pr�fen, ob Taste gedr�ckt ist:
	return (m_pKeystate[Key_ID] ? true:false);
}

