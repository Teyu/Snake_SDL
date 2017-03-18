#ifndef TIMER_H
	#define TIMER_H

#include <SDL.h>

class CTimer
{
public:
	CTimer(); //Konstruktor
	void update();
	float GetElapsed() { return m_fElapsed;}
private:
	float m_fElapsed; //vergangene Zeit seit dem letzten update() Aufruf
	float m_fCurTime; //aktuelle Zeit
	float m_fLastTime; //Zeit des letzten update() Aufrufs
};

#endif