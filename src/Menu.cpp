#include "Menu.h"

/**************************************************************************************************
fragt die Anzahl der Spieler ab und gibt diese zurück
*/

int CMenu::checkbackPlayers()
{
	cout << "Gebe die Anzahl der Spieler ein ( 1 , 2 , 3 ) : " ;
	cin >> input;
	while ( (input != "1") && (input != "2") && (input != "3"))
	{
		cout << "Ung\x81ltige Eingabe!" << endl;
		cin >> input;
	}
	

	return atoi(input.c_str()); //wandelt string in int um
}

/**************************************************************************************************
fragt die Namen der Spieler ab und gibt diese zurück
AOP = Anzahl der Spieler
*/

vector<string> CMenu::checkbackNames(int AOP)
{
	vector<string> output;
	for (int i = 0; i < AOP; i++)
	{
		cout << "Spieler " << i+1 << ", bitte gib deinen Namen ein (oder \"bot\" f" << "\x81" 
			<< "r einen KI-Gegner) : " ;
		cin >> input;
		output.push_back(input);
	}

	return output;
}

/**************************************************************************************************
fragt das Spieltempo ab und gibt dieses zurück
*/

float CMenu::checkbackTempo()
{
	cout << "Geschwindigkeit: (l)angsam , (n)normal, (s)chnell : ";
	cin >> input;
		while ( (input != "l") && (input != "n") && (input != "s"))
	{
		cout << "Ung\x81ltige Eingabe!" << endl;
		cin >> input;
	}
	if (input == "l")
	{
		return 0.075f;
	} else if (input == "n")
	{
		return 0.05f;
	} else if (input == "s")
	{
		return 0.025f;
	}
}

/**************************************************************************************************
gibt dem Spieler aus, dass das Spiel gestartet wird
*/

void CMenu::gameStart()
{
	cout << endl << "Das Spiel wird gestartet ";
	for (int i= 0; i< 3 ; i++)
	{
		SDL_Delay(500);
		cout << ". " ;
	}
	cout << endl << endl;
	SDL_Delay(500);
}

/**************************************************************************************************
gibt dem Spieler eine Wertung aus und öffnet ein Menü
in dem er Einstellungen an der Spieleranzahl und dem Tempo vornehmen kann
Rückgabewert: gibt false zurück, wenn das Spiel neu gestartet werden soll
*/

bool CMenu::gameOver(bool &init, vector<CPlayer> P ,float &Temp)
{
	cout << "GAME OVER!" << endl << endl;

	for (int p = 0; p < P.size(); p++)
	{
		cout << P[p].name << " hat " << P[p].getPoints()
		<< " Fr" << "\x81" << "chte eingesammelt" << endl;
	}
	cout << endl;

	cout << "(n)ochmal  (g)eschwind. " << "\x84" << "ndern  (e)instellungen   (b)eenden" << endl;
	cin >> input;

	//Ungültige Eingabe?
	while ((input != "n") && (input != "g") && (input != "e") && (input != "b"))
	{
		cout << "Ung\x81ltige Eingabe" << endl;
		cin >> input;
	}
	
	if (input == "n")
	{
		gameStart();
		init = false;
		return false;
	} else if (input == "b")
	{
		return true;
	} else if (input == "g")
	{
		Temp = checkbackTempo();
		gameStart();
		init = false;
		return false;
	} else if (input == "e")
	{
		init = true;
		return false;
	}
}