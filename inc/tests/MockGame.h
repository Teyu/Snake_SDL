
#include <Game.h>

class CMockGame : public CGame
{
public:
    CMockGame(CMenu &menu, CFramework &fw) : CGame(menu, fw) {}
    void InitSnake(CSnake &Snake1);
    void InitSnakes(CSnake &Snake1, CSnake &Snake2);
    void InitFood(CFood &Food1);
    void InitFood(CFood &Food1, CFood &Food2);
    bool doCheckCollision(CSnake &Snake, CFood &Food);
    bool doCheckCollision(CSnake &Snake);
    bool doCheckCollision(CSnake &Snake1, CSnake &CSnake2);
};
