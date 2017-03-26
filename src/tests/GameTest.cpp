#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tests/MockMenu.h"
#include "tests/MockFramework.h"
#include "Game.h"

using ::testing::_;
using ::testing::Return;

class GameTest : public ::testing::Test
{
public:
    void TearDown()
    {
        g_pFramework->Del();
    }
};

TEST_F(GameTest, test1)
{
    CMockMenu MockMenu;
    std::vector<std::string> names = {"Player1", "Player2", "Player3"};

    //setting up default behaviour:
    ON_CALL(MockMenu, checkbackPlayers())
            .WillByDefault(Return(names.size()));
    ON_CALL(MockMenu, checkbackNames(_))
            .WillByDefault(Return(names));
    ON_CALL(MockMenu, checkbackTempo())
            .WillByDefault(Return(0.05f));
    ON_CALL(*g_pFramework, Init(_, _, _, _))
            .WillByDefault(Return(true));

    EXPECT_CALL(MockMenu, checkbackPlayers());
    EXPECT_CALL(MockMenu, checkbackNames(_));
    EXPECT_CALL(MockMenu, checkbackTempo());
    EXPECT_CALL(MockMenu, gameStart());
    EXPECT_CALL(*g_pFramework, Init(_, _, _, _));

    CGame Game(MockMenu, *g_pFramework);
    Game.Init(10);
}
