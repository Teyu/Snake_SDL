#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tests/MockSnake.h>

TEST(RigourSnakeTests, moveWithDirectionRight)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::right);

    auto refPos = Snake.getPos();
    refPos.erase(refPos.begin());
    refPos.push_back(refPos.back());
    refPos.back().x += 10u;

    Snake.move();
    auto calcPos = Snake.getPos();
    //TODO: test mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}

TEST(RigourSnakeTests, moveWithDirectionLeft)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::left);

    auto refPos = Snake.getPos();
    refPos.erase(refPos.begin());
    refPos.push_back(refPos.back());
    refPos.back().x -= 10u;

    Snake.move();
    auto calcPos = Snake.getPos();
    //TODO: test mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}

TEST(RigourSnakeTests, moveWithDirectionUp)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::up);

    auto refPos = Snake.getPos();
    refPos.erase(refPos.begin());
    refPos.push_back(refPos.back());
    refPos.back().y -= 10u;

    Snake.move();
    auto calcPos = Snake.getPos();
    //TODO: test mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}

TEST(RigourSnakeTests, moveWithDirectionDown)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::down);

    auto refPos = Snake.getPos();
    refPos.erase(refPos.begin());
    refPos.push_back(refPos.back());
    refPos.back().y += 10u;

    Snake.move();
    auto calcPos = Snake.getPos();
    //TODO: test mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}

TEST(RigourSnakeTests, growWithDirectionRight)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::right);

    auto refPos = Snake.getPos();
    refPos.push_back(refPos.back());
    refPos.back().x += 10u;

    Snake.grow();
    auto calcPos = Snake.getPos();
    //TODO: abfrage mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}

TEST(RigourSnakeTests, growWithDirectionLeft)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::left);

    auto refPos = Snake.getPos();
    refPos.push_back(refPos.back());
    refPos.back().x -= 10u;

    Snake.grow();
    auto calcPos = Snake.getPos();
    //TODO: abfrage mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}

TEST(RigourSnakeTests, growWithDirectionUp)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::up);

    auto refPos = Snake.getPos();
    refPos.push_back(refPos.back());
    refPos.back().y -= 10u;

    Snake.grow();
    auto calcPos = Snake.getPos();
    //TODO: abfrage mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}

TEST(RigourSnakeTests, growWithDirectionDown)
{
    CMockSnake Snake;
    Snake.InitRigourSnakeTest(10u, direction::down);

    auto refPos = Snake.getPos();
    refPos.push_back(refPos.back());
    refPos.back().y += 10u;

    Snake.grow();
    auto calcPos = Snake.getPos();
    //TODO: abfrage mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}
