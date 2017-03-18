#include "Snake.h"
#include <iostream>

/**************************************************************************************************
initialisiert Länge, Größe und Position von Snake
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
	} //wenn kein gültiger Wert übergeben wurde, bleibt die 
		//durch den Konstruktor initialisierte Richtung erhalten: rechts

	//Initialisiere die Länge
	if (len >= 2)//Fordere dabei eine Mindestlänge von 2
	{
		length = len;
	}else
	{
		length = 2;
	}

	//Initialisiere die Größe der Pixel von Snake:
	if (s > 0)//Fordere dabei eine Mindestgröße von 1 (sonst sieht man ihn nicht)
	{
		size = s;
	}else
	{
		size = 1;
	}

	//Prüfe, ob die übergebenen Werte für die Position innerhalb des Bildschirmbereichs sind:
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
		Pos.push_back(Temp); //fügt Element hinten an	
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
bewegt die einzelnen Pixel von Snake unter Berücksichtigung der Richtung um 1 weiter
*/

void CSnake::move()
{
	int n = length - 1;

	//Speichere die Position des Kopfes: Der nachfolgende Teil muss dann an diese Stelle rücken
	SDL_Rect PosAlt = Pos[length-1];

	//Bewege zunächst den Kopf der Schlange in die gewünschte Richtung:
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
ändert die Richtung von Snake, jenachdem ob die Key_ID für rechts oder links übergeben wurde
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
verlängert Snake um ein Pixel
*/

void CSnake::grow()
{
	//füge ein weiteres Pixel hinzu
	//Die Stelle ist dabei abhängig von der Richtung von Snake:
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

	//Snake wird länger:
	length++;
}

/**************************************************************************************************
Zerstöre Snake: Setze Position und Länge auf Nullwerte, Snake wird nicht mehr angezeigt
*/

void CSnake::destroy()
{
	Pos.clear();
	length = 0; 

	d = right;	
}