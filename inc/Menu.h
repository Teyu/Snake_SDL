#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
using namespace std;

class CMenu
{
public:
	CMenu() { input = "";}
	int checkbackPlayers();
    vector<string> checkbackNames(int AOP); // TODO: AOP? (numPlayers)
	float checkbackTempo();	
	void gameStart();
	bool gameOver(bool &init, vector<CPlayer> P ,float &Temp);

private:
	string input;
		
};

#endif
