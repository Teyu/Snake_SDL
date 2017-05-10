#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tests/MockMenu.h"
#include "tests/MockGame.h"
#include "tests/MockFramework.h"
#include "tests/MockSnake.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

ACTION(initTimer) {SDL_Init (SDL_INIT_TIMER); return true;}
ACTION(updateTimer) {g_pTimer->update();}
ACTION(deleteTimer) {SDL_Quit(); g_pTimer->Del();}

class CollisionTest : public ::testing::Test
{
public:
    void SetUp()
    {
        //setting up default behaviour:
        ON_CALL(MockMenu, checkbackTempo())
                .WillByDefault(Return(0.05f));
        ON_CALL(*g_pFramework, Init(_, _, _, _))
                .WillByDefault(initTimer());
        ON_CALL(*g_pFramework, Update())
                .WillByDefault(updateTimer());
        ON_CALL(*g_pFramework, Quit())
                .WillByDefault(deleteTimer());
        ON_CALL(*g_pFramework, KeyDown(_))
                .WillByDefault(Return(false));

        EXPECT_CALL(MockMenu, checkbackPlayers())
                .Times(AtLeast(1));
        EXPECT_CALL(MockMenu, checkbackNames(_))
                .Times(AtLeast(1));
        EXPECT_CALL(MockMenu, checkbackTempo())
                .Times(AtLeast(1));
        EXPECT_CALL(MockMenu, gameStart())
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, Init(_, _, _, _))
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, Update())
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, Clear())
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, drawScene(_,_))
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, BlitSurface(_,_))
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, KeyDown(_))
                .Times(AtLeast(0));
        EXPECT_CALL(*g_pFramework, Flip())
                .Times(AtLeast(1));
        EXPECT_CALL(*g_pFramework, Quit())
                .Times(AtLeast(1));
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
};

TEST_F(CollisionTest, testCheckCollFoodSnakeHead_true) //TODO: use fixed seed
{
    /***************************************
     *         -->
     *     |*|*|*|*|#|
     *
     ***************************************/
    /***************************************
     *
     *             |@|
     *
     ***************************************/

    for (int iterations = 0; iterations < 20; iterations++)
    {
        CSnake Snake; CFood Food(*g_pFramework);
        Snake.init(2*size, size, 5, size, direction::right);
        std::vector<std::string> name = {"Player1"};
        Food.setPos(6*size, size);

        ON_CALL(MockMenu, checkbackPlayers())
                .WillByDefault(Return(1));
        ON_CALL(MockMenu, checkbackNames(_))
                .WillByDefault(Return(name));

        CMockGame Game(MockMenu, *g_pFramework);
        Game.Init(size);
        Game.InitSnake(Snake);
        Game.InitFood(Food);
        ASSERT_TRUE(Game.doCheckCollision(Snake, Food));

        Game.Run();
        auto newSnake = Game.getSnakePos()[0];
        auto newFood = Game.getFoodPos()[0];
        //Snake grows
        ASSERT_EQ(newSnake.size(), Snake.getPos().size()+1);
        ASSERT_TRUE((newSnake[newSnake.size()-1].x == Snake.getPos()[Snake.getPos().size()-1].x + size)
                || ((newSnake[newSnake.size()-1].x == Snake.getPos()[Snake.getPos().size()-1].x + 2*size))); //TODO: replace with getHead
        ASSERT_EQ(newSnake[newSnake.size()-1].y, Snake.getPos()[Snake.getPos().size()-1].y);
        //spawn new Food
        for (size_t i = 0; i < Game.getSnakePos()[0].size(); i++)
        {
            ASSERT_FALSE ((newFood.x == newSnake[i].x) && (newFood.y == newSnake[i].y)); //TODO: use !=operator of SDL_Rect
        }

        Game.Quit();
    }
}

TEST_F(CollisionTest, testCheckCollFoodSnakeHead_false)
{
    /***************************************
     *         -->
     *     |*|*|*|*|#|
     *
     ***************************************/
    /***************************************
     *
     *                |@|
     *
     ***************************************/

    CSnake Snake; CFood Food(*g_pFramework);
    Snake.init(2*size, size, 5, size, direction::right);
    std::vector<std::string> name = {"Player1"};
    Food.setPos(7*size, size);

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(1));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(name));

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitSnake(Snake);
    Game.InitFood(Food);
    ASSERT_FALSE(Game.doCheckCollision(Snake, Food));

    Game.Run();
    auto newSnake = Game.getSnakePos()[0];
    auto newFood = Game.getFoodPos()[0];
    //Snake does not grow
    ASSERT_EQ(newSnake.size(), Snake.getPos().size());
    //Food remains
    ASSERT_EQ(newFood.x, Food.getPos().x); //TODO: use ==operator of SDL_Rect
    ASSERT_EQ(newFood.y, Food.getPos().y);

    Game.Quit();
}

TEST_F(CollisionTest, DISABLED_testCheckCollSnakeWithItsself_true) //TODO: fix
{
    /***************************************
     *
     *     |*|*|#|*|*|*|    |@|
     *         |*|   |*|
     *         |*|   |*|
     *         |*|*|*|*|
     *
     ***************************************/

    CMockSnake Snake; CFood Food(*g_pFramework);
    Snake.InitCollSnakeWithItsself(10u);
    std::vector<std::string> name = {"Player1"};
    Food.setPos(9*size, size);

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(1));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(name));
    ON_CALL(MockMenu, gameOver(_,_,_))
            .WillByDefault(Return(true));
    EXPECT_CALL(MockMenu, gameOver(_,_,_))
            .Times(1);

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitSnake(Snake);
    Game.InitFood(Food);
    ASSERT_TRUE(Game.doCheckCollision(Snake));

    Game.Run();
    // Game Over:
    ASSERT_FALSE(Game.isRunning); //Problem: Kollisionsabfrage funktioniert, aber die Position von Snake
    //innerhalb von CGame::Run() ist plötzlich {{10,20}, {10,10}, {10,0}, {10, -10}, ...}

    if (Game.isRunning)
    {
        Game.Quit(); //TODO: add everywhere necessary
    }
}

TEST_F(CollisionTest, testCheckCollSnakeWithItsself_false)
{
    /***************************************
     *
     *     |*|*|*|*|*|*|    |@|
     *         |#|   |*|
     *         |*|   |*|
     *         |*|*|*|*|
     *
     ***************************************/

    CMockSnake Snake; CFood Food(*g_pFramework);
    Snake.InitNearlyCollSnakeWithItsself(10u);
    std::vector<std::string> name = {"Player1"};
    Food.setPos(9*size, size);

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(1));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(name));

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitSnake(Snake);
    Game.InitFood(Food);
    ASSERT_FALSE(Game.doCheckCollision(Snake));

    Game.Run();
    ASSERT_TRUE(Game.isRunning);

    Game.Quit();
}

TEST_F(CollisionTest, testCheckCollSnakeHeadSnakeHead_true)
{
    /***************************************
     *         -->
     *     |*|*|*|*|#|                |@|
     *
     ***************************************/
    /***************************************
     *                  <--
     *             |#|*|*|*|*|
     *
     ***************************************/

    CSnake Snake1, Snake2; CFood Food(*g_pFramework);
    Snake1.init(2*size, size, 5, size, direction::right);
    Snake2.init(10*size, size, 5, size, direction::left);
    std::vector<std::string> name = {"Player1", "Player2"};
    Food.setPos(16*size, size);

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(2));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(name));
    ON_CALL(MockMenu, gameOver(_,_,_))
            .WillByDefault(Return(true));
    EXPECT_CALL(MockMenu, gameOver(_,_,_))
            .Times(1);

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitSnakes(Snake1, Snake2);
    Game.InitFood(Food);
    ASSERT_TRUE(Game.doCheckCollision(Snake1, Snake2));

    Game.Run();
    ASSERT_FALSE(Game.isRunning);

    if (Game.isRunning)
    {
        Game.Quit();
    }
}

TEST_F(CollisionTest, testCheckCollSnakeHeadSnakeHead_false)
{
    /***************************************
     *         -->
     *     |*|*|*|*|#|                |@|
     *
     ***************************************/
    /***************************************
     *                     <--
     *                |#|*|*|*|*|
     *
     ***************************************/

    CSnake Snake1, Snake2; CFood Food(*g_pFramework);
    Snake1.init(2*size, size, 5, size, direction::right);
    Snake2.init(11*size, size, 5, size, direction::left);
    std::vector<std::string> name = {"Player1", "Player2"};
    Food.setPos(16*size, size);

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(2));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(name));

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitSnakes(Snake1, Snake2);
    Game.InitFood(Food);
    ASSERT_FALSE(Game.doCheckCollision(Snake1, Snake2));

    Game.Run();
    ASSERT_TRUE(Game.isRunning);

    Game.Quit();
}

TEST_F(CollisionTest, testCheckCollSnakeHeadSnakeBody_true)
{
    /***************************************
     *             |#|
     *         --> |*|
     *     |*|*|*|*|#|                |@|
     *             |*|
     *             |*|
     *
     ***************************************/

    CSnake Snake1, Snake2; CFood Food(*g_pFramework);
    Snake1.init(2*size, 2*size, 5, size, direction::right);
    Snake2.init(6*size, 4*size, 5, size, direction::up);
    std::vector<std::string> name = {"Player1", "Player2"};
    Food.setPos(16*size, size);

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(2));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(name));
    ON_CALL(MockMenu, gameOver(_,_,_))
            .WillByDefault(Return(true));
    EXPECT_CALL(MockMenu, gameOver(_,_,_))
            .Times(1);

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitSnakes(Snake1, Snake2);
    Game.InitFood(Food);
    ASSERT_TRUE(Game.doCheckCollision(Snake1, Snake2));

    Game.Run();
    ASSERT_FALSE(Game.isRunning);

    if (Game.isRunning)
    {
        Game.Quit();
    }
}

TEST_F(CollisionTest, testCheckCollSnakeHeadSnakeBody_false)
{
    /***************************************
     *               |#|
     *         -->   |*|
     *     |*|*|*|*|#|*|                |@|
     *               |*|
     *               |*|
     *
     ***************************************/

    CSnake Snake1, Snake2; CFood Food(*g_pFramework);
    Snake1.init(2*size, 2*size, 5, size, direction::right);
    Snake2.init(7*size, 4*size, 5, size, direction::up);
    std::vector<std::string> name = {"Player1", "Player2"};
    Food.setPos(16*size, size);

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(2));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(name));

    CMockGame Game(MockMenu, *g_pFramework);
    Game.Init(size);
    Game.InitSnakes(Snake1, Snake2);
    Game.InitFood(Food);
    ASSERT_FALSE(Game.doCheckCollision(Snake1, Snake2));

    Game.Run();
    ASSERT_TRUE(Game.isRunning);

    Game.Quit();
}
