#include "Screen.h"

/**************************************************************************************************
erzeugt ein Vollbild
*/
bool CScreen::setFullscreen()
{
	int ColorDepth = 16; //Farbtiefe = 16 Bit. Es gibt 8, 16 und 32 Bit, d.h.
						//es wird in diesem Fall 2 Byte Speicher pro Pixel benötigt

	pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
					SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); /* Dies sind sogenannte "Flags"
				 Der letzte Flag legt fest, dass ein "Fullscreen" erzeugt werden soll,
				 lässt man diesen Flag weg, wird ein Fenster erzeugt
				DOUBLEBUF: aktiviert Doublebuffering
				 Das Bild wird erst gerendert, dann angezeigt -> kein Flackern
				HWSURFACE:  Speicher für Surface wird im Videospeicher reserviert,
				 es gibt auch SWSURFACE für den Systemspeicher, allerdings muss die Grafikkarte
				 dann jedes mal über die Hardwareschnittstelle darauf zugreifen
				 -> langsam -> allerdings von jeder Grafikarte unterstützt 
				 RÜCKGABE: Zeiger auf den Bildschirm*/

	//Prüfe, ob alles funktioniert hat
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
setzt das Vollbild zurück
*/
void CScreen::clearScreen()
{
	//füllt den Screen mit Hintergrundfarbe schwarz (bzw. sehr dunkles grau):
	SDL_FillRect(pScreen, NULL, SDL_MapRGB (pScreen->format, 10,10,10)); //füllt einen bestimmten 
					//Ausschnitt mit einer beliebigen Farbe
					//1.Parameter: Zeiger auf die Zieloberfläche
					//2.Parameter: Ausschnitt, der gefüllt werden soll,
					// wenn man hier NULL angibt, wird der gesamte Bildschirm gewählt
					//3. Parameter: bestimmt die gewünschte Farbe
	//SDL_MapRGB:	1. Parameter: aktuelles Farbformat
	//				2. Parameter: Farbintensitäten für Rot, Grün und Blau
	//				 (0,0,0) ist schwarz, (0, 255, 255) wäre gelb, usw.

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
	SDL_Flip(pScreen); //WICHTIG: Da Doublebuffering für den Vollbildmodus eingestellt ist,
			//wird das Rechteck zunächst im Backbuffer gerendert. Erst durch diese Anweisung
			//wird es auf den Screen geladen!
}

/**************************************************************************************************
öffnet den Screen und lässt ihn geöffnet, bis der Anwender ihn schließt
*/

bool CScreen::runScreen()
{
	Game.Init(10);

	//Erzeuge ein Vollbild, und prüfe dabei ob alles geklappt hat:
	if (setFullscreen()== false)
	{
		return false;
	}

	SDL_Event Event; //Struktur des Typs SDL_Event
	//lasse das Vollbild geöffnet, solange bis der Anwender ein Quit-Event auslöst
	while (Game.isRunning == true) 
	{
		if (SDL_PollEvent(&Event)) //diese Funktion füllt die Variable Event und liefert bool zurück
						// Rückgabe true, wenn die Eventstruktur gefüllt wurde
						// Rückgabe false, sonst
		{
			if (Event.type == SDL_QUIT) //Ist das empfangene Event vom Typ SDL_QUIT?
									//(alt F4 gedrückt)
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
		//(alte Bilder werden gelöscht, damit sie nicht übermalt werden) 
		clearScreen();

		Game.Update();
		//solange keine Quit-Event ausgelöst wird kann das Spiel laufen:
		Game.Control(); //steuert das Spiel

		drawGame();
		flipScreen(); //Das Gezeichnete auf den Bildschrim schalten		
	}

	//DAS MUSS NOCH IN DIE WHILE SCHLEIFE UND QUIT BENÖTIGT KEINE RÜCKGABE MEHR
	//Prüfe ob das Spiel beendet wurde, 
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
		vector<vector<SDL_Rect>> SnakePos = Game.getSnakePos(); //Das Spiel gibt die Positionen zurück
		for (int p = 0; p < SnakePos.size(); p++)
		{
			for (int i = static_cast<int> (SnakePos[p].size())-1 ; i >= 0 ; i--)
			{				
				//Jeder Spieler bekommt eine andere Farbe:
				switch(p)
				{
				case 0: //Spieler 1 ist grün:
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

