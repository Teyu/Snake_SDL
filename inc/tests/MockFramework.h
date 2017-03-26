#ifndef MOCKFRAMEWORK_H
#define MOCKFRAMEWORK_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Framework.h"

#undef g_pFramework
#define g_pFramework CMockFrameWork::Get()

class CMockFrameWork : public CFramework, public TSingleton<CMockFrameWork>
{
public:
    MOCK_METHOD4(Init, bool(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen));
    MOCK_METHOD0(Quit, void());
    MOCK_METHOD0(Update, void());
    MOCK_METHOD2(drawScene, void(vector<vector<SDL_Rect>> &SnakePos, vector<SDL_Rect> &FoodPos));
    MOCK_METHOD0(Clear, void());
    MOCK_METHOD0(Flip, void());
    MOCK_METHOD1(KeyDown, bool(int Key_ID));
};

#endif
