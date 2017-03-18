#ifndef SCREEN_H
#define SCREEN_H

#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <string>
using namespace std;

class CScreen
{
public:	
	CScreen() { ScreenWidth = 800;	ScreenHeight = 600;}

	bool runScreen();
private: 
	SDL_Surface *pScreen;	
	CGame Game;
	int ScreenWidth; 
	int ScreenHeight;

	bool setFullscreen();
	void clearScreen();
	void flipScreen();
	void paintRect(SDL_Rect Rec, Uint8 R,  Uint8 G, Uint8 B);
	void drawGame();
};

#endif
