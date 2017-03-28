#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Food.h"
#include "Timer.h"
#include "Menu.h"
#include <string>
#include <math.h>
using namespace std; //TODO: remove std
// TODO: use m_prefix

class CGame
{
public:
    CGame(CMenu &menu, CFramework &fw) :
        isRunning(false), doInit(true), Menu(&menu), Framework(&fw), SnakeTimer(0.0f) {}
    void Init(int resolution);
    void Update(); //TODO: all functions private
    void Control();
    void Render();
    void Run();
    void Quit();
    void setGameTempo( float newTemp) { gameTempo = newTemp;}
    float getGameTempo() {return gameTempo; }
    vector<vector<SDL_Rect>> getSnakePos() {return SPix;}
    vector<SDL_Rect> getFoodPos();

    bool isRunning;
private:
    void ProcessEvents();
    bool isGameOver();

private:
    CMenu * Menu;
    CFramework * Framework;
    vector<CPlayer *> Player;
    vector<string> Names; //TODO: geh�rt zu Player
    vector<CFood *> Food;
    float SnakeTimer;
    float gameTempo;
    int Players;
    int m_resolution;
    vector<vector<SDL_Rect>> SPix; //TODO: nicht n�tig, kann �ber CPlayer abgefragt werden
    bool doInit;

    bool checkCollFoodSnake( int Plyr, int Foo);
    bool checkCollSnakeSnake();
    void spawnFood();

    // TODO: F�r die KI: ACHTUNG: Funktioniert nur f�r einen Bot (m�sste noch als Klasse ausgelagert werden)
    //Vergiss nicht die include math
    bool isFull(SDL_Rect Pix);
    bool isFreeBothSides();
    bool isFreeOneSide(string side);
    bool isNotFreeBothSides();
    void doKI(CPlayer &Bot);
    void goForFood(CFood& F, CPlayer& B);

    bool isColl;
    SDL_Rect Head;
    SDL_Rect Headthen;
    SDL_Rect Heademerg;
    direction actDir;
    direction prevDir;
    bool UTurn;
    int Utimer;
    int UDir;
};

#endif
