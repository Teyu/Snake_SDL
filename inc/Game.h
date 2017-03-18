#ifndef GAME_H
	#define GAME_H

#include "Player.h" 
#include "Food.h"
#include "Tastatur.h"
#include "Timer.h"
#include "Menu.h"
#include <string>
#include <math.h>
using namespace std;

class CGame
{
public:
	CGame() { isRunning = true; doInit = true;} //Konstruktor
	void Init(int res); 
	void Update();
	void Control();	
	bool Quit();
	void setGameTempo( float newTemp) { gameTempo = newTemp;}
	vector<vector<SDL_Rect>> getSnakePos() {return SPix;}  
	vector<SDL_Rect> getFoodPos();

 	bool isRunning;

private:	
	CMenu Menu;
	vector<CPlayer> Player; 
	vector<string> Names;
	vector<CFood> Food;
	CTimer timer;
	float SnakeTimer;
	float gameTempo;
	int Players;
	int resolution;
	vector<vector<SDL_Rect>> SPix; //Positionen der Schlangen
	bool doInit;

	bool checkCollFoodSnake( int Plyr, int Foo);
	bool checkCollSnakeSnake();
	void spawnFood();

	//Für die KI: ACHTUNG: Funktioniert nur für einen Bot (müsste noch als Klasse ausgelagert werden)
	//Vergiss nicht die include math
	bool isFull(SDL_Rect Pix);
	bool isFreeBothSides();
	bool isFreeOneSide(string side);
	bool isNotFreeBothSides();
	void doKI(CPlayer &Bot);
	void goForFood(CFood F, CPlayer& B);

	bool isColl;
	SDL_Rect Head;
	SDL_Rect Headthen;
	SDL_Rect Heademerg;
	enum direction{up, down, right, left};
	direction actDir;
	direction prevDir;
	bool UTurn;
	int Utimer;
	int UDir;
};

#endif