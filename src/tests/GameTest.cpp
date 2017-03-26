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

class GameTest : public ::testing::Test //TODO: Systemtest
{
public:
    void TearDown()
    {
        g_pFramework->Del();
    }
};

TEST_F(GameTest, testInitWith1Players)
{
    CMockMenu MockMenu;
    int numPlayers = 1;
    float gameTempo = 0.05f;
    int size = 10;
    std::vector<std::string> names = {"Player1"};

    //setting up default behaviour:
    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(numPlayers));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(names));
    ON_CALL(MockMenu, checkbackTempo())
            .WillByDefault(Return(gameTempo));
    ON_CALL(*g_pFramework, Init(_, _, _, _))
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
    }

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    ASSERT_FALSE(Game.isRunning);

    auto Snakes = Game.getSnakePos();
    ASSERT_EQ(numPlayers, Snakes.size());
    EXPECT_EQ(Snakes[0][4], SDL_Rect({4*size, 3*size, size, size})); //TODO: replace with getHead (rest is part of SnakeTest)
    EXPECT_EQ(size, Snakes[0][4].h);
    EXPECT_EQ(size, Snakes[0][4].w);

    auto Foods = Game.getFoodPos();
    ASSERT_EQ(numPlayers, Foods.size());
    EXPECT_EQ(size, Foods[0].h);
    EXPECT_EQ(size, Foods[0].w);

    ASSERT_FLOAT_EQ(gameTempo, Game.getGameTempo());
}

TEST_F(GameTest, testInitWith2Players)
{
    CMockMenu MockMenu;
    int numPlayers = 2;
    float gameTempo = 0.05f;
    int size = 10;
    std::vector<std::string> names = {"Player1", "Player2"};

    //setting up default behaviour:
    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(numPlayers));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(names));
    ON_CALL(MockMenu, checkbackTempo())
            .WillByDefault(Return(gameTempo));
    ON_CALL(*g_pFramework, Init(_, _, _, _))
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
    }

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    ASSERT_FALSE(Game.isRunning);

    auto Snakes = Game.getSnakePos();
    ASSERT_EQ(numPlayers, Snakes.size());
    EXPECT_EQ(Snakes[0][4], SDL_Rect({4*size, 3*size, size, size})); //TODO: replace with getHead (rest is part of SnakeTest)
    EXPECT_EQ(Snakes[1][4], SDL_Rect({400-1*size, 600-5*size, size, size})); //TODO: remove magic numbers (#define)
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
}

TEST_F(GameTest, testInitWith3Players)
{
    CMockMenu MockMenu;
    int numPlayers = 3;
    float gameTempo = 0.05f;
    int size = 10;
    std::vector<std::string> names = {"Player1", "Player2", "Player3"};

    //setting up default behaviour:
    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(numPlayers));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(names));
    ON_CALL(MockMenu, checkbackTempo())
            .WillByDefault(Return(gameTempo));
    ON_CALL(*g_pFramework, Init(_, _, _, _))
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
    }

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    ASSERT_FALSE(Game.isRunning);

    auto Snakes = Game.getSnakePos();
    ASSERT_EQ(numPlayers, Snakes.size());
    EXPECT_EQ(Snakes[0][4], SDL_Rect({4*size, 3*size, size, size})); //TODO: replace with getHead (rest is part of SnakeTest)
    EXPECT_EQ(Snakes[1][4], SDL_Rect({400-1*size, 600-5*size, size, size})); //TODO: remove magic numbers (#define)
    EXPECT_EQ(Snakes[2][4], SDL_Rect({800-9*size, 300-size, size, size}));
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
}

TEST_F(GameTest, testRunAndTriggerQuitEvent) //TODO: später auch Quit testen
{
    CMockMenu MockMenu;
    int numPlayers = 3;
    float gameTempo = 0.05f;
    int size = 10;
    std::vector<std::string> names = {"Player1", "Player2", "Player3"};

    //setting up default behaviour:
    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(numPlayers));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(names));
    ON_CALL(MockMenu, checkbackTempo())
            .WillByDefault(Return(gameTempo));
    ON_CALL(MockMenu, gameOver(_, _, _))
            .WillByDefault(Return(true));
    ON_CALL(*g_pFramework, Init(_, _, _, _))
            .WillByDefault(Return(true));
    ON_CALL(*g_pFramework, KeyDown(_))
            .WillByDefault(Return(false));
    ON_CALL(*g_pFramework, KeyDown(SDLK_ESCAPE))
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
        EXPECT_CALL(MockMenu, gameOver(_, _, _))
                .Times(Exactly(1));
        //TODO: after removed from main: g_pFramework->Quit
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


    EXPECT_CALL(*g_pFramework, Update())
            .Times(AtLeast(1));
    EXPECT_CALL(*g_pFramework, KeyDown(_))
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*g_pFramework, KeyDown(SDLK_ESCAPE))
        .WillOnce(Return(true));

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.Run();
    ASSERT_FALSE(Game.isRunning);
}

//TODO: kollisionsabfragen gehören nicht mehr zum systemtest

