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
    CFood();
    SDL_Rect getPos() { return Pos;}
    void setSize(uint newSize);
    void Render();
    bool spawn();
    void destroy() {isAlive = false;}

private:
	SDL_Rect Pos;
	int size;
    bool isAlive;

    void setPos(uint x, uint y);
};

#endif
