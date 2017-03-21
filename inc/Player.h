#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Snake.h"
#include "Framework.h"
using namespace std;

class CPlayer: public CSnake
{
public:
    ~CPlayer(){}
    CPlayer() { KI = false;}

    void Init(int KeyL, int KeyR, int startPosX, int startPosY, direction startDir, int res);
	void Update();
	void growSnake();
	int getPoints() {return Points;}
    void setKI(bool nKI) {KI = nKI;} // TODO: neue Klasse CBot:CSnake (lagere gemeinsame Eigenschaften nach CSnake aus)
	bool isKI() { return KI;}

	string name;

private:
	int Points;
	bool KeyLock; 
	bool growLock;
	int KeyLeft;
	int KeyRight;
    bool KI;
};

#endif
