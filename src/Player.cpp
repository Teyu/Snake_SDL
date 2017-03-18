#include "Player.h"

/**************************************************************************************************
Initialisiert die Membervariablen, sowie die Basisklasse CSnake
*/

void CPlayer::Init(int KeyL, int KeyR, int startPosX, int startPosY, string startDir, int res)
{
	KeyLock = false; //dient dazu, dass Snake nur einmal die Richtung ändert, wenn man
		//eine Taste drückt. Andernfalls würde er während der ganzen Zeit, die man die Taste gedrückt hält,
		//die Richtung ändern -> sogenanntes "Autofire"
	growLock = false; //analog für das Wachsen von Snake, beim Aufsammeln von Früchten
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
Aktualisiert die KeyBoardeingaben und ändert entsprechend die Richtung von Snake
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
Snake wächst und seine Punktzahl erhöht sich
*/

void CPlayer::growSnake()
{ 
	Points++;
	grow();
}