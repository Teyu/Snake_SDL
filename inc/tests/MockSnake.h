#ifndef MOCKSNAKE_H //TODO: insert this everywhere
#define MOCKSNAKE_H

#include <Snake.h>

class CMockSnake : public CSnake
{
public:
    void InitRigourSnakeTest(uint s ,direction dir);
    void InitNearlyCollSnakeWithItsself(uint s);
    void InitCollSnakeWithItsself(uint s);
};

#endif
