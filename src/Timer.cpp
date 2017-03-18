#include "Timer.h"

//Konstruktor:
CTimer::CTimer()
{
	m_fCurTime = 0.0f; //float-Datentypen enden immer mit einem f
	m_fLastTime = SDL_GetTicks() / 1000.0f; //liefert die Zeit in Millisekunden zurück,
					// die seit dem initialisieren der SDL vergangen ist.
					// Rechne dies noch in Sekunden um.
	m_fElapsed = 0.0f;
}

//Update:
void CTimer::update()
{
	//aktuelle Zeit:
	m_fCurTime = SDL_GetTicks() / 1000.0f;

	//Zeitdifferenz seit dem letzten Aufruf von update():
	m_fElapsed = m_fCurTime - m_fLastTime;
	m_fLastTime = m_fCurTime; //letzter Zeitpunkt zudem update() aufgerufen wurde
}
