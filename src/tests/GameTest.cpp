#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tests/MockMenu.h"
#include "tests/MockFramework.h"
#include "Game.h"

using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::AtMost;

ACTION(initTimer) {SDL_Init (SDL_INIT_TIMER); return true;}
ACTION(updateTimer) {g_pTimer->update();}
ACTION(deleteTimer) {SDL_Quit(); g_pTimer->Del();}

bool operator !=(const SDL_Rect &a, const SDL_Rect &b)
{
    return !(a == b);
}

class GameTest : public ::testing::Test //TODO: Systemtest
{
public:
    void SetUp()
    {
        //setting up default behaviour:
        ON_CALL(MockMenu, checkbackPlayers())
                .WillByDefault(Return(numPlayers));
        ON_CALL(MockMenu, checkbackNames(_))
                .WillByDefault(Return(names));
        ON_CALL(MockMenu, checkbackTempo())
                .WillByDefault(Return(gameTempo));
        ON_CALL(*g_pFramework, Init(_, _, _, _))
                .WillByDefault(initTimer());
        ON_CALL(*g_pFramework, Update())
                .WillByDefault(updateTimer());
        ON_CALL(*g_pFramework, Quit())
                .WillByDefault(deleteTimer());
    }

    void TearDown()
    {
        //TODO: remove after removed from main
        g_pFramework->Quit();
        g_pFramework->Del();
    }

public:
    CMockMenu MockMenu;
    int numPlayers = 3;
    float gameTempo = 0.05f;
    int size = 10;
    std::vector<std::string> names = {"Player1", "Player2", "Player3"};
    SDL_Rect Player1StartPos = {40, 30, 10, 10};
    SDL_Rect Player2StartPos = {800/2-10, 600-50, 10, 10}; //TODO: remove magic numbers
    SDL_Rect Player3StartPos = {800-90, 600/2-10, 10, 10};
};

TEST_F(GameTest, testInit)
{
    {
        InSequence dummy;
        EXPECT_CALL(MockMenu, checkbackPlayers())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackNames(numPlayers))
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackTempo())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, gameStart())
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Init(_, _, _, _)) //TODO: enter screenWidth,screenHeight after definition (see below)
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Update())
                .Times(AtLeast(0));
        EXPECT_CALL(*g_pFramework, Quit())
                .Times(Exactly(1));
    }

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    ASSERT_TRUE(Game.isRunning);

    auto Snakes = Game.getSnakePos();
    ASSERT_EQ(numPlayers, Snakes.size());
    EXPECT_EQ(Snakes[0][4], Player1StartPos); //TODO: replace with getHead (rest is part of SnakeTest)
    EXPECT_EQ(Snakes[1][4], Player2StartPos); //TODO: remove magic numbers (#define)
    EXPECT_EQ(Snakes[2][4], Player3StartPos);
    for (size_t i = 0; i < Snakes.size(); i++)
    {
        EXPECT_EQ(size, Snakes[i][4].h);
        EXPECT_EQ(size, Snakes[i][4].w);
    }

    auto Foods = Game.getFoodPos();
    ASSERT_EQ(numPlayers, Foods.size());
    for (size_t i = 0; i < Foods.size(); i++)
    {
        EXPECT_EQ(size, Foods[i].h);
        EXPECT_EQ(size, Foods[i].w);
    }

    ASSERT_FLOAT_EQ(gameTempo, Game.getGameTempo());
    Game.Quit();
}

TEST_F(GameTest, testRunAndTriggerQuitEvent)
{
    ON_CALL(*g_pFramework, KeyDown(_))
            .WillByDefault(Return(false));
    ON_CALL(*g_pFramework, KeyDown(SDLK_ESCAPE))
            .WillByDefault(Return(true));
    ON_CALL(MockMenu, gameOver(_,_,_))
            .WillByDefault(Return(true));

    {
        InSequence dummy;
        EXPECT_CALL(MockMenu, checkbackPlayers())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackNames(numPlayers))
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackTempo())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, gameStart())
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Init(_, _, _, _)) //TODO: enter screenWidth,screenHeight after definition (see below)
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Update())
                .Times(AtLeast(1));
        EXPECT_CALL(MockMenu, gameOver(_,_,_))
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Quit())
                .Times(Exactly(1));
    }

    EXPECT_CALL(*g_pFramework, KeyDown(_))
            .WillRepeatedly(Return(false));
    EXPECT_CALL(*g_pFramework, KeyDown(SDLK_ESCAPE))
            .WillOnce(Return(true));

    {
        InSequence dummy;

        EXPECT_CALL(*g_pFramework, Clear())
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, drawScene(_,_))
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, BlitSurface(_,_))
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, Flip())
                .Times(AtLeast(1));
    }

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.Run();
    ASSERT_FALSE(Game.isRunning);
}

TEST_F(GameTest, testRunGameOverAndRestart)
{
    ON_CALL(*g_pFramework, KeyDown(_))
            .WillByDefault(Return(false));
    ON_CALL(*g_pFramework, KeyDown(SDLK_ESCAPE))
            .WillByDefault(Return(true));
    ON_CALL(MockMenu, gameOver(_,_,_))
            .WillByDefault(Return(false));

    {
        InSequence dummy;

        EXPECT_CALL(MockMenu, checkbackPlayers())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackNames(numPlayers))
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackTempo())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, gameStart())
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Init(_, _, _, _)) //TODO: enter screenWidth,screenHeight after definition (see below)
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Update())
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, Quit())
                .Times(Exactly(1));
    }


    EXPECT_CALL(*g_pFramework, KeyDown(_))
            .WillRepeatedly(Return(false));
    EXPECT_CALL(*g_pFramework, KeyDown(SDLK_ESCAPE))
            .WillRepeatedly(Return(true));

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    for (int i = 0; i < 5; i++)
    {
        EXPECT_CALL(MockMenu, checkbackPlayers())
                .Times(AtMost(1));
        EXPECT_CALL(MockMenu, checkbackNames(numPlayers))
                .Times(AtMost(1));
        EXPECT_CALL(MockMenu, checkbackTempo())
                .Times(AtMost(1));

        {
            InSequence dummy;

            EXPECT_CALL(MockMenu, gameOver(_,_,_))
                    .Times(Exactly(1))
                    .WillOnce(Return(false));
            EXPECT_CALL(MockMenu, gameStart())
                    .Times(Exactly(1));
            EXPECT_CALL(*g_pFramework, Init(_, _, _, _)) //TODO: enter screenWidth,screenHeight after definition (see below)
                    .Times(Exactly(1));
        }

        {
            InSequence dummy;

            EXPECT_CALL(*g_pFramework, Clear())
                    .Times(AtLeast(1));
            EXPECT_CALL(*g_pFramework, drawScene(_,_))
                    .Times(AtLeast(1));
            EXPECT_CALL(*g_pFramework, BlitSurface(_,_))
                    .Times(AtLeast(1));
            EXPECT_CALL(*g_pFramework, Flip())
                    .Times(AtLeast(1));
        }

        Game.Run();
        ASSERT_TRUE(Game.isRunning);
    }

    //force Quit
    Game.Quit();
}

TEST_F(GameTest, testRunFiniteLoop)
{
    ON_CALL(*g_pFramework, KeyDown(_))
            .WillByDefault(Return(false));
    ON_CALL(*g_pFramework, KeyDown(SDLK_ESCAPE))
            .WillByDefault(Return(false));
    ON_CALL(MockMenu, gameOver(_,_,_))
            .WillByDefault(Return(true));
    {
        InSequence dummy;
        EXPECT_CALL(MockMenu, checkbackPlayers())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackNames(numPlayers))
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, checkbackTempo())
                .Times(Exactly(1));
        EXPECT_CALL(MockMenu, gameStart())
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Init(_, _, _, _)) //TODO: enter screenWidth,screenHeight after definition (see below)
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, KeyDown(_))
                .WillRepeatedly(Return(false));
        EXPECT_CALL(*g_pFramework, Quit())
                .Times(Exactly(1));
    }

    EXPECT_CALL(*g_pFramework, Update())
            .Times(AtLeast(1));
    EXPECT_CALL(MockMenu, gameOver(_,_,_))
            .Times(Exactly(0));

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    for (int i = 0; i < 200; i++)
    {
        {
            InSequence dummy;

            EXPECT_CALL(*g_pFramework, Clear())
                .Times(AtLeast(1));
            EXPECT_CALL(*g_pFramework, drawScene(_,_))
                .Times(AtLeast(1));
            EXPECT_CALL(*g_pFramework, BlitSurface(_,_))
                .Times(AtLeast(1));
            EXPECT_CALL(*g_pFramework, Flip())
                .Times(AtLeast(1));
        }
        Game.Run();
        ASSERT_TRUE(Game.isRunning);
    }

    //expect movement:
    auto Snakes = Game.getSnakePos(); //TODO: replace with GetHead();
    EXPECT_NE( Player1StartPos, Snakes[0][4]);
    EXPECT_NE( Player2StartPos, Snakes[1][4]);
    EXPECT_NE( Player3StartPos, Snakes[2][4]);

    //force Quit:
    Game.Quit();
}

TEST_F (GameTest, DISABLED_testTriggerKeyMoveEvent_Player1)
{
    //TODO: implement
}

TEST_F (GameTest, DISABLED_testTriggerKeyMoveEvent_Player2)
{
    //TODO: implement
}

TEST_F (GameTest, DISABLED_testTriggerKeyMoveEvent_Player3)
{
    //TODO: implement
}

//TODO: kollisionsabfragen gehören nicht mehr zum systemtest

