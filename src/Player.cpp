#include "Player.h"

/**************************************************************************************************
Initialisiert die Membervariablen, sowie die Basisklasse CSnake
*/

void CPlayer::Init(int KeyL, int KeyR, int startPosX, int startPosY, string startDir, int res)
{
	KeyLock = false; //dient dazu, dass Snake nur einmal die Richtung �ndert, wenn man
		//eine Taste dr�ckt. Andernfalls w�rde er w�hrend der ganzen Zeit, die man die Taste gedr�ckt h�lt,
		//die Richtung �ndern -> sogenanntes "Autofire"
	growLock = false; //analog f�r das Wachsen von Snake, beim Aufsammeln von Fr�chten
	Points = 0;
	length = 0;
	KeyLeft = KeyL;
	KeyRight = KeyR;

	//initialisiere Snake:
	//const int startLength = 5;

	//ZUM TESTEN:
	int startLength = 5;

	init(startPosX, startPosY, startLength, res, startDir); 

}

/**************************************************************************************************
Aktualisiert die KeyBoardeingaben und �ndert entsprechend die Richtung von Snake
*/

void CPlayer::Update()
{

if (KI == false)
{
	KeyBoard.update();

	if ((KeyBoard.KeyDown(KeyRight)) && (KeyLock == false))
		{
			changeDirection(KeyRight);
			KeyLock = true;
		}
		if ((KeyBoard.KeyDown(KeyLeft)) && (KeyLock == false))
		{
			changeDirection(KeyLeft);
			KeyLock = true;
		}
		if ((KeyBoard.KeyDown(KeyLeft) == false) && (KeyBoard.KeyDown(KeyRight) == false))
		{
			KeyLock = false;
		}
}
}

/**************************************************************************************************
Snake w�chst und seine Punktzahl erh�ht sich
*/

void CPlayer::growSnake()
{ 
	Points++;
	grow();
}