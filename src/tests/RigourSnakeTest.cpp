#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tests/MockSnake.h>

TEST(RigourSnakeTests, moveWithDirectionRight)
{
    MockSnake Snake;
    Snake.Init(10u, direction::right);

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
    MockSnake Snake;
    Snake.Init(10u, direction::left);

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
    MockSnake Snake;
    Snake.Init(10u, direction::up);

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
    MockSnake Snake;
    Snake.Init(10u, direction::down);

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
    MockSnake Snake;
    Snake.Init(10u, direction::right);

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
    MockSnake Snake;
    Snake.Init(10u, direction::left);

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
    MockSnake Snake;
    Snake.Init(10u, direction::up);

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
    MockSnake Snake;
    Snake.Init(10u, direction::down);

    auto refPos = Snake.getPos();
    refPos.push_back(refPos.back());
    refPos.back().y += 10u;

    Snake.grow();
    auto calcPos = Snake.getPos();
    //TODO: abfrage mit getHead
    EXPECT_THAT(refPos, ::testing::ElementsAreArray(calcPos));
}
