#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Player.h"
#include "tests/MockFramework.h"

using ::testing::Return;
using ::testing::AtLeast;

class PlayerTest : public ::testing::Test
{
public:
    void TearDown()
    {
        g_pFramework->Del();
    }

public:
    int m_KeyLeft = SDLK_LEFT;
    int m_KeyRight = SDLK_RIGHT;
    int m_size = 10;
    int m_startPosX = m_size, m_startPosY = m_size;
};

TEST_F(PlayerTest, testInit)
{
    CPlayer Player(*g_pFramework);
    Player.Init(m_KeyLeft, m_KeyRight, m_startPosX, m_startPosY, direction::right, m_size);

    EXPECT_EQ(direction::right, Player.getDir());
    EXPECT_EQ(0, Player.getPoints());
    EXPECT_EQ(SDL_Rect({m_startPosX, m_startPosY, m_size, m_size}), Player.getPos()[0]); //TODO: replace with getHead and set Head position during Init
}

TEST_F(PlayerTest, testTriggerKeyEventMoveRight)
{
    CPlayer Player(*g_pFramework);
    Player.Init(m_KeyLeft, m_KeyRight, m_startPosX, m_startPosY, direction::right, m_size);

    ON_CALL(*g_pFramework, KeyDown(SDLK_RIGHT))
            .WillByDefault(Return(true));
    ON_CALL(*g_pFramework, KeyDown(SDLK_LEFT))
            .WillByDefault(Return(false));
    EXPECT_CALL(*g_pFramework, KeyDown(SDLK_RIGHT))
            .Times(AtLeast(1));
    EXPECT_CALL(*g_pFramework, KeyDown(SDLK_LEFT))
            .Times(AtLeast(0));

    Player.Update();
    EXPECT_EQ(direction::down, Player.getDir());
}

TEST_F(PlayerTest, testTriggerKeyEventMoveLeft)
{
    CPlayer Player(*g_pFramework);
    Player.Init(m_KeyLeft, m_KeyRight, m_startPosX, m_startPosY, direction::right, m_size);

    ON_CALL(*g_pFramework, KeyDown(SDLK_RIGHT))
            .WillByDefault(Return(false));
    ON_CALL(*g_pFramework, KeyDown(SDLK_LEFT))
            .WillByDefault(Return(true));
    EXPECT_CALL(*g_pFramework, KeyDown(SDLK_RIGHT))
            .Times(AtLeast(0));
    EXPECT_CALL(*g_pFramework, KeyDown(SDLK_LEFT))
            .Times(AtLeast(1));

    Player.Update();
    EXPECT_EQ(direction::up, Player.getDir());
}

TEST_F(PlayerTest, testGainPointsAfterGrowing)
{
    CPlayer Player(*g_pFramework);
    Player.Init(m_KeyLeft, m_KeyRight, m_startPosX, m_startPosY, direction::right, m_size);

    Player.growSnake();
    EXPECT_EQ(1, Player.getPoints());
}
