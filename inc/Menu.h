#ifndef MENU_H
#define MENU_H

#include "Player.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
using namespace std;

class CMenu
{
public:
    virtual ~CMenu(){}
    virtual int checkbackPlayers() = 0;
    virtual vector<string> checkbackNames(int AOP) = 0; // TODO: AOP? (numPlayers)
    virtual float checkbackTempo() = 0;
    virtual void gameStart() = 0;
    virtual bool gameOver(bool &init, vector<CPlayer> P ,float &Temp) = 0;
};

class CConcreteMenu : public CMenu
{
public:
    CConcreteMenu() { input = "";}
    ~CConcreteMenu(){}
    int checkbackPlayers();
    vector<string> checkbackNames(int AOP); // TODO: AOP? (numPlayers)
    float checkbackTempo();
    void gameStart();
    bool gameOver(bool &init, vector<CPlayer> P ,float &Temp);
private:
    string input;

};

#endif
