#ifndef FOOD_H
#define FOOD_H

#include <SDL.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Sprite.h"
using namespace std;

class CFood
{
public:
    CFood(CFramework &fw);
    ~CFood() {delete m_Sprite;}
    SDL_Rect getPos() { return m_Sprite->GetRect();} //REMOVE
    void setSize(uint newSize);
    void Render();
    bool spawn();
    void destroy() {isAlive = false;}

private:
    CSprite * m_Sprite;
	int size;
    bool isAlive;

    void setPos(uint x, uint y);
};

#endif
