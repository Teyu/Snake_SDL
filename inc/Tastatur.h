#ifndef FRAMEWORK_H
	#define FRAMEWORK_H

#include <iostream>
#include "Timer.h"
using namespace std;

class CTastatur
{
public:
	CTastatur(); //Konstruktor
	void update();
	bool KeyDown(int Key_ID);

private:
	Uint8 *m_pKeystate; //Array für aktuellen Tastaturstatus
	CTimer timer;
};

#endif


