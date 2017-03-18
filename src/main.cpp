#include "Screen.h"
#include <iostream>
using namespace std;

int main( int argc, char *argv[])
{
	//Info:
	cout << "***************Willkommen beim Multiplayermodus von Snake!***************" << endl
		<< endl << endl;
	cout << "Ziel des Spiels:" << endl;
	cout << "Wer die meisten Fr" << "\x81" << "chte einsammelt gewinnt!" << endl
		<< endl << endl;
	cout << "Steuerung: " << endl;
	cout << "Spieler 1 (gr" << "\x81" << "n) benutzt die Pfeiltasten links/rechts." << endl;
	cout << "Spieler 2 (blau) benutzt die Tasten A und D." << endl;
	cout << "Spieler 3 (gelb) benutzt die Tasten L und K." << endl << endl;

	CScreen Screen;

	//SDL initialisieren: Die Flags geben an welche Teilbereiche initialisiert werden sollen
	//Hier: Grafik und Timer
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
		cout << "SDL konnte nicht initialisiert werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError () << endl; //Diese Funktion gibt eine Fehlermeldung 
		//als string zur�ck. Da im Hintergrund eine Konsole l�uft, kann dies dort ausgegeben werden


		//SDL beenden: Die Funktion k�mmert sich darum, dass der von mir reservierte Speicher
		// durch pScreen wieder frei gegeben wird. Dies ist WICHTIG. Dieser Speicher soll nicht
		// manuell freiegegeben werden
		SDL_Quit();

		return 0;
	}

	//Lasse die Bildschirmausgabe laufen, und pr�fe ob dabei alles geklappt hat:
	if (Screen.runScreen()== false)
	{
		cout << "Fehler beim erstellen des Vollbildmodus" << endl;
		SDL_Quit();
		return 0;
	}

	//ACHTUNG: Achte darauf, dass diese Funktion auf jeden Fall aufgerufen wird! 
	// Sonst bleibt das Programm wom�glich h�ngen
	SDL_Quit();
	return (0);
}

/*
Konfigurationen zum erstellen der Release-Datei:
	Stelle Unter Verweise/Konfigurationseigenschaften oben links auf Release um
	F�hre dann alle Konfigurationsschritte aus SDL_Test nochmal durch...

*/

