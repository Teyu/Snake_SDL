#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Snake.h>

bool operator ==(const SDL_Rect &a, const SDL_Rect &b) //TODO: outsource later
{
    return ((a.x == b.x) && (a.y == b.y) && (a.h == b.h) && (a.w == b.w));
}

//TODO: Testfälle mit gewundener Schlange ? Benötige mockSnake -> neuer Test rigourSnakeTest

TEST(SnakeTest, initWithDirectionRightTest)
{
    uint posX = 15u;
    uint posY = 30u;
    uint length = 5u;
    uint size = 10u;
    auto dir = direction::right;

    CSnake Snake;
    Snake.init(posX, posY, length, size, dir);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{15u, posY, size, size},
                                    {25u, posY, size, size},
                                    {35u, posY, size, size},
                                    {45u, posY, size, size},
                                    {55u, posY, size, size}};
    ASSERT_EQ(length, Pos.size());
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
    //TODO: abfrage mit getHead (posX, posY)
    ASSERT_EQ(dir, Snake.getDir());
}

TEST(SnakeTest, initWithDirectionLeftTest)
{
    uint posX = 150u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;
    auto dir = direction::left;

    CSnake Snake;
    Snake.init(posX, posY, length, size, dir);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{150u, posY, size, size},
                                    {140u, posY, size, size},
                                    {130u, posY, size, size},
                                    {120u, posY, size, size},
                                    {110u, posY, size, size}};
    ASSERT_EQ(length, Pos.size());
    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
    ASSERT_EQ(dir, Snake.getDir());
}

TEST(SnakeTest, initWithDirectionDownTest)
{
    uint posX = 15u;
    uint posY = 30u;
    uint length = 5u;
    uint size = 10u;
    auto dir = direction::down;

    CSnake Snake;
    Snake.init(posX, posY, length, size, dir);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, 30u, size, size},
                                    {posX, 40u, size, size},
                                    {posX, 50u, size, size},
                                    {posX, 60u, size, size},
                                    {posX, 70u, size, size}};
    ASSERT_EQ(length, Pos.size());
    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
    ASSERT_EQ(dir, Snake.getDir());
}

TEST(SnakeTest, initWithDirectionUpTest)
{
    uint posX = 150u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;
    auto dir = direction::up;

    CSnake Snake;
    Snake.init(posX, posY, length, size, dir);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, 300u, size, size},
                                    {posX, 290u, size, size},
                                    {posX, 280u, size, size},
                                    {posX, 270u, size, size},
                                    {posX, 260u, size, size}};
    ASSERT_EQ(length, Pos.size());
    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
    ASSERT_EQ(dir, Snake.getDir());
}

TEST(SnakeTest, initWithXPosOutOfScreenBordersDirectionRightTest)
{
    uint posX = 800u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::right);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX-5u*size, posY, size, size},
                                    {posX-4u*size, posY, size, size},
                                    {posX-3u*size, posY, size, size},
                                    {posX-2u*size, posY, size, size},
                                    {posX-1u*size, posY, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}


TEST(SnakeTest, initWithXPosOutOfScreenBordersDirectionLeftTest)
{
    uint posX = 800u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::left);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX-5u*size, posY, size, size},
                                    {posX-6u*size, posY, size, size},
                                    {posX-7u*size, posY, size, size},
                                    {posX-8u*size, posY, size, size},
                                    {posX-9u*size, posY, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, initWithYPosOutOfScreenBordersDirectionUpTest)
{
    uint posX = 150u;
    uint posY = 600u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::up);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, posY-5u*size, size, size},
                                    {posX, posY-6u*size, size, size},
                                    {posX, posY-7u*size, size, size},
                                    {posX, posY-8u*size, size, size},
                                    {posX, posY-9u*size, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, initWithYPosOutOfScreenBordersDirectionDownTest)
{
    uint posX = 150u;
    uint posY = 600u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::down);

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, posY-5u*size, size, size},
                                    {posX, posY-4u*size, size, size},
                                    {posX, posY-3u*size, size, size},
                                    {posX, posY-2u*size, size, size},
                                    {posX, posY-1u*size, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, moveWithDirectionRight)
{
    uint posX = 15u;
    uint posY = 30u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::right);
    Snake.move();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{25u, posY, size, size},
                                    {35u, posY, size, size},
                                    {45u, posY, size, size},
                                    {55u, posY, size, size},
                                    {65u, posY, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, moveWithDirectionLeft)
{
    uint posX = 150u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::left);
    Snake.move();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{140u, posY, size, size},
                                    {130u, posY, size, size},
                                    {120u, posY, size, size},
                                    {110u, posY, size, size},
                                    {100u, posY, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, moveWithDirectionUp)
{
    uint posX = 150u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::up);
    Snake.move();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, 290u, size, size},
                                    {posX, 280u, size, size},
                                    {posX, 270u, size, size},
                                    {posX, 260u, size, size},
                                    {posX, 250u, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, moveWithDirectionDown)
{
    uint posX = 15u;
    uint posY = 30u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::down);
    Snake.move();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, 40u, size, size},
                                    {posX, 50u, size, size},
                                    {posX, 60u, size, size},
                                    {posX, 70u, size, size},
                                    {posX, 80u, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, changeDirectionRight)
{
    uint posX = 100u;
    uint posY = 100u;
    uint length = 5u;
    uint size = 10u;

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::right);

        Snake.changeDirection(SDLK_RIGHT);
        ASSERT_EQ(direction::down, Snake.getDir());
        ASSERT_EQ(direction::right, Snake.getPrevD());
    }

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::down);

        Snake.changeDirection(SDLK_RIGHT);
        ASSERT_EQ(direction::left, Snake.getDir());
        ASSERT_EQ(direction::down, Snake.getPrevD());
    }

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::left);

        Snake.changeDirection(SDLK_RIGHT);
        ASSERT_EQ(direction::up, Snake.getDir());
        ASSERT_EQ(direction::left, Snake.getPrevD());
    }

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::up);

        Snake.changeDirection(SDLK_RIGHT);
        ASSERT_EQ(direction::right, Snake.getDir());
        ASSERT_EQ(direction::up, Snake.getPrevD());
    }
}

TEST(SnakeTest, changeDirectionLeft)
{
    uint posX = 100u;
    uint posY = 100u;
    uint length = 5u;
    uint size = 10u;

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::right);

        Snake.changeDirection(SDLK_LEFT);
        ASSERT_EQ(direction::up, Snake.getDir());
        ASSERT_EQ(direction::right, Snake.getPrevD());
    }

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::down);

        Snake.changeDirection(SDLK_LEFT);
        ASSERT_EQ(direction::right, Snake.getDir());
        ASSERT_EQ(direction::down, Snake.getPrevD());
    }

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::left);

        Snake.changeDirection(SDLK_LEFT);
        ASSERT_EQ(direction::down, Snake.getDir());
        ASSERT_EQ(direction::left, Snake.getPrevD());
    }

    {
        CSnake Snake;
        Snake.init(posX, posY, length, size, direction::up);

        Snake.changeDirection(SDLK_LEFT);
        ASSERT_EQ(direction::left, Snake.getDir());
        ASSERT_EQ(direction::up, Snake.getPrevD());
    }
}

TEST(SnakeTest, growWithDirectionRight)
{
    uint posX = 15u;
    uint posY = 30u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::right);
    Snake.grow();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{15u, posY, size, size},
                                    {25u, posY, size, size},
                                    {35u, posY, size, size},
                                    {45u, posY, size, size},
                                    {55u, posY, size, size},
                                    {65u, posY, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, growWithDirectionLeft)
{
    uint posX = 150u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::left);
    Snake.grow();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{150u, posY, size, size},
                                    {140u, posY, size, size},
                                    {130u, posY, size, size},
                                    {120u, posY, size, size},
                                    {110u, posY, size, size},
                                    {100u, posY, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, growWithDirectionUp)
{
    uint posX = 150u;
    uint posY = 300u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::up);
    Snake.grow();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, 300u, size, size},
                                    {posX, 290u, size, size},
                                    {posX, 280u, size, size},
                                    {posX, 270u, size, size},
                                    {posX, 260u, size, size},
                                    {posX, 250u, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, growWithDirectionDown)
{
    uint posX = 15u;
    uint posY = 30u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::down);
    Snake.grow();

    auto Pos = Snake.getPos();
    std::vector<SDL_Rect> refPos = {{posX, 30u, size, size},
                                    {posX, 40u, size, size},
                                    {posX, 50u, size, size},
                                    {posX, 60u, size, size},
                                    {posX, 70u, size, size},
                                    {posX, 80u, size, size}};

    //TODO: abfrage mit getHead
    ASSERT_THAT(refPos, ::testing::ElementsAreArray(Pos));
}

TEST(SnakeTest, destroySnake)
{
    uint posX = 15u;
    uint posY = 30u;
    uint length = 5u;
    uint size = 10u;

    CSnake Snake;
    Snake.init(posX, posY, length, size, direction::down);
    Snake.destroy();

    ASSERT_EQ(0u, Snake.getPos().size());
}
