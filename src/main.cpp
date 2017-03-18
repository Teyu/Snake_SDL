#include "Screen.h"
#include <iostream>
using namespace std;

int main( int argc, char *argv[])
{
    cout << "***************Welcome to Multiplayer version of Snake!***************" << endl
            //TODO: display version
		<< endl << endl;
    cout << "Goal of the Game:" << endl;
    cout << "Whoever selects the highest number of fruits wins!" << endl
		<< endl << endl;
    cout << "Controls: " << endl;
    cout << "Player 1 (green) uses the keys left and right." << endl;
    cout << "Player 2 (blue) uses the keys A and D." << endl;
    cout << "Player 3 (yellow) uses the keys L and K." << endl << endl;

	CScreen Screen;

	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
	{
        cout << "could not initialize SDL!" << endl;
        cout << "error message: " << SDL_GetError () << endl;
		SDL_Quit();

        return 1;
	}

	if (Screen.runScreen()== false)
	{
        cout << "error occured while running full screen mode" << endl;
		SDL_Quit();

        return 1;
	}

	SDL_Quit();
    return 0;
}

