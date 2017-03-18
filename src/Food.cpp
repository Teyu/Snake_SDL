#include "Food.h"

CFood::CFood() 
{ 
	isAlive = false; 
	Pos.x = 0; 
	Pos.y = 0; 
	Pos.w = 0; 
	Pos.h = 0; 
	size = 0;

	//Zufallsgenerator: WICHTIG, DIESER SOLLTE NUR EINMAL GENERIERT WERDEN,
	//SONST WIRD IMMER DIE GLEICHE ZUFALLSZAHL ERZEUGT!!!!!!!!!!!!!!!!!
	time_t t;
	srand( time(&t) );}

/**************************************************************************************************
Setzt die Position von Food und korrigiert ggf.ung�ltige �bergebene Parameter
*/

void CFood::setPos(int x, int y)
{
	//Ist die �bergebene Position im g�ltigen Bereich, ersetze die alte durch die neue:
	if (((x >= 0) && (x <= 800 - size)) && ((y >= 0) && (y <= 600 - size)))
	{
		Pos.x = x;
		Pos.y = y;
	}else
	{
	//korrigiere die Position, wenn sie nicht in einem g�ltigen Bereich liegt:
	if (x < 0)
	{
		Pos.x = 0;
	}else if (x > 800 - size)
	{
		Pos.x = 800 - size;
	}
	if (y < 0)
	{
		Pos.x = 0;
	}else if (y > 600 - size)
	{
		Pos.x = 600 - size;
	}
	}

}

/**************************************************************************************************
�ndert die Gr��e von Food
*/

void CFood::setSize(int newSize)
{
	//Lege eine Mindestgr��e fest:
	if (newSize > 0)
	{
		size = newSize;
	}else
	{
		size = 1; //Mindestgr��e
	}

	Pos.h = size;
	Pos.w = size;
}

/**************************************************************************************************
Setzt eine zuf�llige Position f�r Food, 
allerdings nur, wenn noch keines existiert!
*/

void CFood::spawn()
{
	if (isAlive == false)
	{

	//Position zuf�llig bestimmen:
	int Posx = (rand() % (800/size - 1))*size ; //Das Ergebnis muss ein Vielfaches von size sein
	int Posy = (rand() % (600/size - 1))*size ;

	setPos(Posx, Posy);

	isAlive = true;
	}
}