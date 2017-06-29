#include "tests/MockGame.h"

void CMockGame::InitFood(CFood &Food1)
{
    Food[0]->setPos(Food1.getPos().x, Food1.getPos().y);
}

void CMockGame::InitFood(CFood &Food1, CFood &Food2)
{
    Food[0]->setPos(Food1.getPos().x, Food1.getPos().y);
    Food[1]->setPos(Food2.getPos().x, Food2.getPos().y);
}

void CMockGame::InitSnake(CSnake &Snake1)
{
    Player[0]->init(Snake1.getPos()[0].x, Snake1.getPos()[0].y, Snake1.getPos().size(), Snake1.getPos()[0].h, Snake1.getDir());
}

void CMockGame::InitSnakes(CSnake &Snake1, CSnake &Snake2)
{
    Player[0]->init(Snake1.getPos()[0].x, Snake1.getPos()[0].y, Snake1.getPos().size(), Snake1.getPos()[0].h, Snake1.getDir());
    Player[1]->init(Snake2.getPos()[0].x, Snake2.getPos()[0].y, Snake2.getPos().size(), Snake2.getPos()[0].h, Snake2.getDir());

    //TODO: remove after SPix has been removed:
    SPix[0].clear(); SPix[1].clear();
    SPix[0] = Player[0]->getPos();
    SPix[1] = Player[1]->getPos();
}

bool CMockGame::doCheckCollision(CSnake &Snake, CFood &Food)
{
    return checkCollision(Snake, Food);
}

bool CMockGame::doCheckCollision(CSnake &Snake)
{
    return checkCollision(Snake);
}

bool CMockGame::doCheckCollision(CSnake &Snake1, CSnake &Snake2)
{
    return checkCollision(Snake1, Snake2);
}
