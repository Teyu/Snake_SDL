#include "Game.h"
#include <iostream>

#include <SnakeConfig.h>

using namespace std;

int main( int argc, char *argv[])
{
    cout << "***************Welcome to Multiplayer version of Snake!***************" << endl
        << endl << endl;
    cout << "Snake Version " << SNAKE_VERSION_MAJOR << "." << SNAKE_VERSION_MINOR << endl
        << endl << endl;
    cout << "Goal of the Game:" << endl;
    cout << "Whoever selects the highest number of fruits wins!" << endl
		<< endl << endl;
    cout << "Controls: " << endl;
    cout << "Player 1 (green) uses the keys left and right." << endl;
    cout << "Player 2 (blue) uses the keys A and D." << endl;
    cout << "Player 3 (yellow) uses the keys L and K." << endl << endl;

    CRealMenu Menu;
    CGame Game(Menu, *g_pFramework);

    Game.Init(10);
    while (Game.isRunning)
    {
        Game.Run();
    }
    //Game.Quit();

    g_pFramework->Quit(); //TODO: nach CGame verlagern
    g_pFramework->Del();

    return 0;
}

