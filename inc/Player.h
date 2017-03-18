#ifndef PLAYER_H
	#define PLAYER_H

#include <string>
#include "Snake.h"
#include "Tastatur.h"
using namespace std;

class CPlayer: public CSnake
{
public:
	//TEST:
	CPlayer() { KI = false;}
	void Init(int KeyL, int KeyR, int startPosX, int startPosY, string startDir, int res);
	void Update();
	void growSnake();
	int getPoints() {return Points;}
	void setKI(bool nKI) {KI = nKI;}
	bool isKI() { return KI;}

	string name;

private:
	int Points;
	bool KeyLock; 
	bool growLock;
	int KeyLeft;
	int KeyRight;
	bool KI;
	CTastatur KeyBoard;
};

#endif