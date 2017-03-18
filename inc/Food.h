#ifndef FOOD_H
	#define FOOD_H

#include <SDL.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

class CFood
{
public:
	CFood(); //Konstruktor
	SDL_Rect getPos() { return Pos;} //Gebe an den Screen zum Zeichnen weiter
	void setSize(int newSize);
	void spawn();
	void destroy() {isAlive= false;}	

private:
	SDL_Rect Pos;
	int size;
	bool isAlive; //true, solange das Futter noch nicht gegessen wurde

	void setPos(int x, int y);
};

#endif