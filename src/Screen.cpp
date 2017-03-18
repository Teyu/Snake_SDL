#include "Screen.h"

/**************************************************************************************************
erzeugt ein Vollbild
*/
bool CScreen::setFullscreen()
{
	int ColorDepth = 16; //Farbtiefe = 16 Bit. Es gibt 8, 16 und 32 Bit, d.h.
						//es wird in diesem Fall 2 Byte Speicher pro Pixel ben�tigt

	pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
					SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); /* Dies sind sogenannte "Flags"
				 Der letzte Flag legt fest, dass ein "Fullscreen" erzeugt werden soll,
				 l�sst man diesen Flag weg, wird ein Fenster erzeugt
				DOUBLEBUF: aktiviert Doublebuffering
				 Das Bild wird erst gerendert, dann angezeigt -> kein Flackern
				HWSURFACE:  Speicher f�r Surface wird im Videospeicher reserviert,
				 es gibt auch SWSURFACE f�r den Systemspeicher, allerdings muss die Grafikkarte
				 dann jedes mal �ber die Hardwareschnittstelle darauf zugreifen
				 -> langsam -> allerdings von jeder Grafikarte unterst�tzt 
				 R�CKGABE: Zeiger auf den Bildschirm*/

	//Pr�fe, ob alles funktioniert hat
	if (pScreen == NULL)
	{
		cout << "Videomodus konnte nicht gesetzt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		SDL_Quit();

		return false;

	}

	return true;
}

/**************************************************************************************************
setzt das Vollbild zur�ck
*/
void CScreen::clearScreen()
{
	//f�llt den Screen mit Hintergrundfarbe schwarz (bzw. sehr dunkles grau):
	SDL_FillRect(pScreen, NULL, SDL_MapRGB (pScreen->format, 10,10,10)); //f�llt einen bestimmten 
					//Ausschnitt mit einer beliebigen Farbe
					//1.Parameter: Zeiger auf die Zieloberfl�che
					//2.Parameter: Ausschnitt, der gef�llt werden soll,
					// wenn man hier NULL angibt, wird der gesamte Bildschirm gew�hlt
					//3. Parameter: bestimmt die gew�nschte Farbe
	//SDL_MapRGB:	1. Parameter: aktuelles Farbformat
	//				2. Parameter: Farbintensit�ten f�r Rot, Gr�n und Blau
	//				 (0,0,0) ist schwarz, (0, 255, 255) w�re gelb, usw.

}

/**************************************************************************************************
zeichnet ein Rechteck auf den Screen
*/

void CScreen::paintRect(SDL_Rect Rec, Uint8 R,  Uint8 G, Uint8 B)
{
	SDL_FillRect(pScreen, &Rec, SDL_MapRGB(pScreen->format, R ,G ,B));
}

/**************************************************************************************************
schaltet den Backbuffer auf den Screen
*/

void CScreen::flipScreen()
{
	SDL_Flip(pScreen); //WICHTIG: Da Doublebuffering f�r den Vollbildmodus eingestellt ist,
			//wird das Rechteck zun�chst im Backbuffer gerendert. Erst durch diese Anweisung
			//wird es auf den Screen geladen!
}

/**************************************************************************************************
�ffnet den Screen und l�sst ihn ge�ffnet, bis der Anwender ihn schlie�t
*/

bool CScreen::runScreen()
{
	Game.Init(10);

	//Erzeuge ein Vollbild, und pr�fe dabei ob alles geklappt hat:
	if (setFullscreen()== false)
	{
		return false;
	}

	SDL_Event Event; //Struktur des Typs SDL_Event
	//lasse das Vollbild ge�ffnet, solange bis der Anwender ein Quit-Event ausl�st
	while (Game.isRunning == true) 
	{
		if (SDL_PollEvent(&Event)) //diese Funktion f�llt die Variable Event und liefert bool zur�ck
						// R�ckgabe true, wenn die Eventstruktur gef�llt wurde
						// R�ckgabe false, sonst
		{
			if (Event.type == SDL_QUIT) //Ist das empfangene Event vom Typ SDL_QUIT?
									//(alt F4 gedr�ckt)
			{
				Game.isRunning = false; 
			}
			else if (Event.type == SDL_KEYDOWN) 
			{
				if (Event.key.keysym.sym == SDLK_ESCAPE)
				Game.isRunning = false; 
			}
		}

		//Reinige den Screen 
		//(alte Bilder werden gel�scht, damit sie nicht �bermalt werden) 
		clearScreen();

		Game.Update();
		//solange keine Quit-Event ausgel�st wird kann das Spiel laufen:
		Game.Control(); //steuert das Spiel

		drawGame();
		flipScreen(); //Das Gezeichnete auf den Bildschrim schalten		
	}

	//DAS MUSS NOCH IN DIE WHILE SCHLEIFE UND QUIT BEN�TIGT KEINE R�CKGABE MEHR
	//Pr�fe ob das Spiel beendet wurde, 
	//wenn nicht, rufe die Funktion wieder auf:
	if (Game.Quit()==false)
	{
		if (runScreen()== false)
		{
			cout << "Fehler beim erstellen des Vollbildmodus" << endl;
			SDL_Quit();
		}
	}
}

/**************************************************************************************************
Zeichnet Snake und Essen
*/

void CScreen::drawGame()
{
	//Snake zeichnen:
		vector<vector<SDL_Rect>> SnakePos = Game.getSnakePos(); //Das Spiel gibt die Positionen zur�ck
		for (int p = 0; p < SnakePos.size(); p++)
		{
			for (int i = static_cast<int> (SnakePos[p].size())-1 ; i >= 0 ; i--)
			{				
				//Jeder Spieler bekommt eine andere Farbe:
				switch(p)
				{
				case 0: //Spieler 1 ist gr�n:
					paintRect(SnakePos[p][i], 0 , 255, 0);
					break;
				case 1: //Spieler 2 ist blau:
					paintRect(SnakePos[p][i], 0 , 0, 255);
					break;
				case 2: //Spieler 3 ist gelb:
					paintRect(SnakePos[p][i], 255 , 255, 0);
					break;
				}		 
			}
		}

		//Food zeichnen:
		for (int i=0; i < Game.getFoodPos().size(); i++)
		{
			paintRect(Game.getFoodPos()[i], 255, 0 , 0); // in rot
		}
}

