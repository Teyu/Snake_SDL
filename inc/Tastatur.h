#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include "Timer.h"
using namespace std;

class CTastatur
{
public:
    CTastatur();
	void update();
	bool KeyDown(int Key_ID);

private:
    Uint8 *m_pKeystate;
	CTimer timer;
};

#endif


