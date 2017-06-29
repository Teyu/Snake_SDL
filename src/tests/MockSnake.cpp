#include "tests/MockSnake.h"

void CMockSnake::InitRigourSnakeTest(uint s ,direction dir)
{
    d = dir;
    length = 29;
    size = s;

    /***************************************
     *                       |*|
     *     |#|*|*|*|*|       |*|
     *             |*|   |*|*|*|
     *             |*|   |*|*|*|*|*|
     *             |*|           |*|
     *             |*|           |*|
     *             |*|*|*|*|*|*|*|*|
     *
     ***************************************/


    Pos = { {110, 0 , size, size},
            {110, 10, size, size}, {110, 20, size, size}, {100 , 20, size, size}, {90, 20, size, size},
            {90 , 30, size, size}, {100, 30, size, size}, {110, 30, size, size}, {120, 30, size, size},
            {130, 30, size, size}, {130, 40, size, size}, {130, 50, size, size}, {130, 60, size, size},
            {120, 60, size, size}, {110, 60, size, size}, {100, 60, size, size}, {90 , 60, size, size},
            {80 , 60, size, size}, {70 , 60, size, size}, {60 , 60, size, size}, {60 , 50, size, size},
            {60 , 40, size, size}, {60 , 30, size, size}, {60 , 20, size, size}, {60 , 10, size, size},
            {50 , 10, size, size}, {40 , 10, size, size}, {30 , 10, size, size}, {20 , 10, size, size} };

    if (dir == direction::right)
    {
        length = 30;
        SDL_Rect addPos = {20, 0, size, size};
        Pos.push_back((SDL_Rect) addPos);
    }
}


void CMockSnake::InitNearlyCollSnakeWithItsself(uint s)
{
    d = direction::up;
    length = 14;
    size = s;

    /***************************************
     *
     *     |*|*|*|*|*|*|
     *         |#|   |*|
     *         |*|   |*|
     *         |*|*|*|*|
     *
     ***************************************/

    Pos = {{2*size, 1*size, size, size}, {3*size, 1*size, size, size}, {4*size, 1*size, size, size}, {5*size, 1*size, size, size},
           {6*size, 1*size, size, size}, {7*size, 1*size, size, size}, {7*size, 2*size, size, size}, {7*size, 3*size, size, size},
           {7*size, 4*size, size, size}, {6*size, 4*size, size, size}, {5*size, 4*size, size, size}, {4*size, 4*size, size, size},
           {4*size, 3*size, size, size}, {4*size, 2*size, size, size}};
}

void CMockSnake::InitCollSnakeWithItsself(uint s)
{

    /***************************************
     *
     *     |*|*|#|*|*|*|
     *         |*|   |*|
     *         |*|   |*|
     *         |*|*|*|*|
     *
     ***************************************/

    InitNearlyCollSnakeWithItsself(s);
    length++;
    Pos.push_back({4*size, 1*size, size, size});
}
