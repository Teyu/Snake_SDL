#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tests/MockGame.h"
#include "Game.h"

//#undef g_pFramework
//#define g_pFramework CMockFramework::Get()

//TODO: rename MockGame -> MockMenu
//TODO: create MockFramework.cpp oder mocken ?

using ::testing::Return;

TEST(GameTest, test1)
{
    CMockMenu MockMenu;
    CGame Game(MockMenu);
    std::vector<std::string> names = {"Player1", "Player2", "Player3"};

    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(3)); //setting default value
    ON_CALL(MockMenu, checkbackNames(3))
            .WillByDefault(Return(names)); //setting default value
    ON_CALL(MockMenu, checkbackTempo())
            .WillByDefault(Return(0.05f)); //setting default value

    EXPECT_CALL(MockMenu, checkbackPlayers())
            .WillOnce(Return(3));
    //TEST
    //std::cout << "checkbackPlayers: " << MockMenu.checkbackPlayers() << std::endl;
    //

    Game.Init(10);
}
