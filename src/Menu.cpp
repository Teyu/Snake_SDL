#include "Menu.h"

/**************************************************************************************************
returns the number of players
*/

int CRealMenu::checkbackPlayers()
{
    cout << "Enter the number of players ( 1 , 2 , 3 ) : " ;
	cin >> input;
	while ( (input != "1") && (input != "2") && (input != "3"))
	{
        cout << "invalid input!" << endl;
		cin >> input;
	}
	
	return atoi(input.c_str()); //wandelt string in int um
}

/**************************************************************************************************
returns the players' names
*/

vector<string> CRealMenu::checkbackNames(int AOP)
{
	vector<string> output;
	for (int i = 0; i < AOP; i++)
	{
        cout << "Player " << i+1 << ", please enter your name (type \"bot\" for a computerized enemy) : " ;
		cin >> input;
		output.push_back(input);
	}

	return output;
}

/**************************************************************************************************
returns the game tempo
*/

float CRealMenu::checkbackTempo()
{
    cout << "game tempo: (s)low , (n)normal, (f)ast : ";
	cin >> input;
        while ( (input != "s") && (input != "n") && (input != "f"))
	{
        cout << "invalid input!" << endl;
		cin >> input;
	}
    if (input == "s")
	{
		return 0.075f;
	} else if (input == "n")
	{
		return 0.05f;
    } else if (input == "f")
	{
		return 0.025f;
	}
}

/**************************************************************************************************
displays the start of the game
*/

void CRealMenu::gameStart()
{
    cout << endl << "The game is starting ";
	for (int i= 0; i< 3 ; i++)
	{
		SDL_Delay(500);
		cout << ". " ;
	}
	cout << endl << endl;
	SDL_Delay(500);
}

/**************************************************************************************************
displays a feedback to the player and opens a menu to edit settings and/or to restart the game
*/

bool CRealMenu::gameOver(bool &init, vector<CPlayer> P ,float &Temp)
//TODO: funktion startAgain(), die zurückgibt ob neu gestartet werden soll
//TODO: funktion update(), die Player den Einstellungen entsprechend updated
{
	cout << "GAME OVER!" << endl << endl;

	for (int p = 0; p < P.size(); p++)
	{
        cout << P[p].name << " selected " << P[p].getPoints()
        << " fruits!" << endl;
	}
	cout << endl;

    cout << "(r)estart  (t)empo  (s)ettings  (q)uit" << endl;
	cin >> input;

    while ((input != "r") && (input != "t") && (input != "s") && (input != "q"))
	{
        cout << "invalid input" << endl;
		cin >> input;
	}
	
    if (input == "r")
	{
		gameStart();
        init = false; //TODO: remove
		return false;
    } else if (input == "q")
	{
		return true;
    } else if (input == "t")
	{
		Temp = checkbackTempo();
		gameStart();
        init = false; //TODO: remove
		return false;
    } else if (input == "s")
	{
        init = true; //TODO: remove (s.a. update)
		return false;
	}
}
