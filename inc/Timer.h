#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class CTimer
{
public:
    CTimer();
	void update();
	float GetElapsed() { return m_fElapsed;}
private:
    float m_fElapsed;
    float m_fCurTime;
    float m_fLastTime;
};

#endif
