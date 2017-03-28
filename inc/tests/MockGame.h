#include <Game.h>

class CMockGame : public CGame
{
public:
    CMockGame(CMenu &menu, CFramework &fw) : CGame(menu, fw) {}
    void InitCollidingSnakes(uint size);
};

void CMockGame::InitCollidingSnakes(uint size)
{
    /***************************************
     *          ->            <-
     *     |*|*|*|*|#|   |#|*|*|*|*|
     *
     ***************************************/

    Player[0]->init(2*size, size, 5, size, direction::right);
    Player[1]->init(13*size, size, 5, size, direction::left);

    //TODO: remove after SPix has been removed:
    SPix[0].clear(); SPix[1].clear();
    SPix[0] = Player[0]->getPos();
    SPix[1] = Player[1]->getPos();
}
