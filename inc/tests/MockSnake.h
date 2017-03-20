#include <Snake.h>

class MockSnake : public CSnake
{
public:
    void Init(uint s ,direction dir);
};

void MockSnake::Init(uint s ,direction dir)
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
