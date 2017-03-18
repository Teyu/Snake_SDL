#include "Snake.h"
#include <iostream>

/**************************************************************************************************
initialisiert L�nge, Gr��e und Position von Snake
*/

void CSnake::init(int Px, int Py, int len, int s, string dir)
{
	//Initialisiere die Startrichtung:
	array<string,4> Richtung = {"up", "down", "right", "left"};

	for (int i = 0; i < Richtung.size() ; i++)
	{
		if (dir == Richtung[i])
		{
			d = direction(i);
		}
	} //wenn kein g�ltiger Wert �bergeben wurde, bleibt die 
		//durch den Konstruktor initialisierte Richtung erhalten: rechts

	//Initialisiere die L�nge
	if (len >= 2)//Fordere dabei eine Mindestl�nge von 2
	{
		length = len;
	}else
	{
		length = 2;
	}

	//Initialisiere die Gr��e der Pixel von Snake:
	if (s > 0)//Fordere dabei eine Mindestgr��e von 1 (sonst sieht man ihn nicht)
	{
		size = s;
	}else
	{
		size = 1;
	}

	//Pr�fe, ob die �bergebenen Werte f�r die Position innerhalb des Bildschirmbereichs sind:
	if (Px<0)
	{
		Px=0;
	}else if (Px > 800 - size*length)
	{
		Px=800-size*length;
	}
	if (Py<0)
	{
		Py=0;
	}else if (Py > 600-size*length)
	{
		Py=600-size*length;
	}

	//Initialisiere die Position von Snake:
	SDL_Rect Temp;
	Temp.x = Px;
	Temp.y = Py;
	Temp.h = size;
	Temp.w = size;

	for (int i=0; i< length; i++)
	{
		Pos.push_back(Temp); //f�gt Element hinten an	
		switch(d) //je nach Startrichtung beginnt Snake in einer anderen Position:
		{ 
		case right:
			Temp.x += size; 
			break;
		case left:
			Temp.x -= size;
			break;
		case down:
			Temp.y += size;
			break;
		case up:
			Temp.y -= size;
			break;
		}
	}
}

/**************************************************************************************************
bewegt die einzelnen Pixel von Snake unter Ber�cksichtigung der Richtung um 1 weiter
*/

void CSnake::move()
{
	int n = length - 1;

	//Speichere die Position des Kopfes: Der nachfolgende Teil muss dann an diese Stelle r�cken
	SDL_Rect PosAlt = Pos[length-1];

	//Bewege zun�chst den Kopf der Schlange in die gew�nschte Richtung:
	switch (d)
	{
	case right:
		if ((Pos[n].x < (800 - size)) && (Pos[n].x >=0))
				{
					Pos[n].x += size;
				}else
				{
					Pos[n].x = 0;
				}
		break;
	case down:
		if ((Pos[n].y < (600 - size)) && (Pos[n].y >= 0))
				{
					Pos[n].y += size;
				}else
				{
					Pos[n].y = 0;
				}
		break;
	case left:
		if ((Pos[n].x > 0) && (Pos[n].x <= (800- size)))
				{
					Pos[n].x -= size;
				}else
				{
					Pos[n].x = 800-size;
				}
		break;
	case up:
		if ((Pos[n].y > 0) && (Pos[n].y <= (600-size)))
				{
					Pos[n].y -= size;
				}else
				{
					Pos[n].y = 600-size;
				}
		break;
	}

	for( int i = n-1; i >= 0; i--)
	{
		SDL_Rect tmp = Pos[i];
		Pos[i] = PosAlt; //Setze nachfolgenden Teil der Schlange an die alte Pos des vorigen Teils
		PosAlt = tmp; //speichere die alte Pos
	}

}

/**************************************************************************************************
�ndert die Richtung von Snake, jenachdem ob die Key_ID f�r rechts oder links �bergeben wurde
*/

void CSnake::changeDirection(int k)
{
	prevD = d;
	if ((k == SDLK_RIGHT) || (k == SDLK_l) || (k == SDLK_d))
	{
		switch(d)
		{
		case right:
			d = down;
			break;
		case down:
			d = left;
			break;
		case left:
			d = up;
			break;
		case up:
			d = right;
			break;
		}
	}
	if (((k == SDLK_LEFT) || (k == SDLK_a)) || (k == SDLK_k))
	{
		switch(d)
		{
		case right:
			d = up;
			break;
		case down:
			d = right;
			break;
		case left:
			d = down;
			break;
		case up:
			d = left;
			break;
		}
	}
}

/**************************************************************************************************
verl�ngert Snake um ein Pixel
*/

void CSnake::grow()
{
	//f�ge ein weiteres Pixel hinzu
	//Die Stelle ist dabei abh�ngig von der Richtung von Snake:
	SDL_Rect tmp;
	tmp = Pos[length-1];

	switch(d)
	{
	case right:
		tmp.x += size;
		break;
	case down:
		tmp.y += size;
		break;
	case left:
		tmp.x -= size;
		break;
	case up:
		tmp.y -= size;
		break;
	}

	Pos.push_back(tmp);

	//Snake wird l�nger:
	length++;
}

/**************************************************************************************************
Zerst�re Snake: Setze Position und L�nge auf Nullwerte, Snake wird nicht mehr angezeigt
*/

void CSnake::destroy()
{
	Pos.clear();
	length = 0; 

	d = right;	
}