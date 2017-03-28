#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tests/MockMenu.h"
#include "tests/MockFramework.h"
#include "tests/MockGame.h"

using ::testing::_;
using ::testing::Return;
using ::testing::InSequence;
using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::AtMost;
using ::testing::Expectation;

ACTION(initTimer) {SDL_Init (SDL_INIT_TIMER); return true;}
ACTION(updateTimer) {g_pTimer->update();}
ACTION(deleteTimer) {SDL_Quit(); g_pTimer->Del();}

bool operator !=(const SDL_Rect &a, const SDL_Rect &b)
{
    return !(a == b);
}

class GameTest : public ::testing::Test
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
        g_pFramework->Del(); //TODO: set expectation after moved to main
    }

public:
    CMockMenu MockMenu;
    int size = 10;
    int numPlayers = 3;
    float gameTempo = 0.05f;
    std::vector<std::string> names = {"Player1", "Player2", "Player3"};
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
    Game.Quit();
    ASSERT_FALSE(Game.isRunning);
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

TEST_F(GameTest, testRunAndTriggerGameOver)
{
    ON_CALL(*g_pFramework, KeyDown(_))
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
        EXPECT_CALL(*g_pFramework, Update())
                .Times(AtLeast(1));
        EXPECT_CALL(MockMenu, gameOver(_,_,_))
                .Times(Exactly(1));
        EXPECT_CALL(*g_pFramework, Quit())
                .Times(Exactly(1));
    }

    EXPECT_CALL(*g_pFramework, KeyDown(_))
            .WillRepeatedly(Return(false));

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitCollidingSnakes(size);
    ASSERT_TRUE(Game.isRunning);
    for (size_t i = 0; i < 200; i++)
    {
        if (Game.isRunning)
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
        }
    }
    ASSERT_FALSE(Game.isRunning);
}

TEST_F(GameTest, testRunTriggerQuitEventAndRestart)
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

            // TODO: über all an diese Stellen im Test gehört die Quit erwartung sobald aus main verschoben
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

TEST_F(GameTest, testRunTriggerGameOverAndRestart)
{
    ON_CALL(*g_pFramework, KeyDown(_))
            .WillByDefault(Return(false));
    ON_CALL(MockMenu, gameOver(_,_,_))
            .WillByDefault(Return(false));

    Expectation game_over = EXPECT_CALL(MockMenu, gameOver(_,_,_))
            .Times(Exactly(1));
    Expectation game_start = EXPECT_CALL(MockMenu, gameStart())
            .Times(Exactly(1))
            .After(game_over);

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

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitCollidingSnakes(size);
    for (size_t i = 0; i < 200; i++)
    {
        EXPECT_CALL(MockMenu, checkbackPlayers())
                .Times(AtMost(1));
        EXPECT_CALL(MockMenu, checkbackNames(numPlayers))
                .Times(AtMost(1));
        EXPECT_CALL(MockMenu, checkbackTempo())
                .Times(AtMost(1));
        EXPECT_CALL(*g_pFramework, Init(_, _, _, _)) //TODO: enter screenWidth,screenHeight after definition (see below)
                .Times(AtMost(1))
                .After(game_over, game_start);

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
        EXPECT_CALL(*g_pFramework, Update())
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, Quit())
                .Times(Exactly(1));
    }

    EXPECT_CALL(*g_pFramework, KeyDown(_))
            .WillRepeatedly(Return(false));
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

    //force Quit:
    Game.Quit();
}

