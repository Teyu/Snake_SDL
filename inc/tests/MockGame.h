#ifndef MOCKGAME_H
#define MOCKGAME_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Menu.h"
#include "Framework.h"

using namespace std;

class CMockMenu : public CMenu
{
public:
    MOCK_METHOD0(checkbackPlayers, int());
    MOCK_METHOD1(checkbackNames, vector<string>(int AOP));
    MOCK_METHOD0(checkbackTempo, float());
    MOCK_METHOD0(gameStart, void());
    MOCK_METHOD3(gameOver, bool(bool &init, vector<CPlayer> P ,float &Temp));
};

/*class CMockFrameWork : public CFramework
{
public:
    MOCK_METHOD4(Init, bool(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen));
    MOCK_METHOD0(Quit, void());
    MOCK_METHOD0(Update, void());
    MOCK_METHOD2(drawScene, void(vector<vector<SDL_Rect>> &SnakePos, vector<SDL_Rect> &FoodPos));
    MOCK_METHOD0(Clear, void());
    MOCK_METHOD0(Flip, void());
    MOCK_METHOD1(KeyDown, bool(int Key_ID));
    MOCK_METHOD0(GetScreen, SDL_Surface *());
};*/

#endif
