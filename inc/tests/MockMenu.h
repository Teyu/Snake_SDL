#ifndef MOCKGAME_H
#define MOCKGAME_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Menu.h"

using namespace std;

class CMockMenu : public CMenu
{
public:
    MOCK_METHOD0(checkbackPlayers, int());
    MOCK_METHOD1(checkbackNames, vector<string>(int AOP));
    MOCK_METHOD0(checkbackTempo, float());
    MOCK_METHOD0(gameStart, void());
    MOCK_METHOD3(gameOver, bool(bool &init, vector<CPlayer *> P ,float &Temp));
};

#endif
