#include "Screen.h"

/**************************************************************************************************
generates a full screen, return true when succeeded otherwise false
*/
bool CScreen::setFullscreen()
{
    int ColorDepth = 16;

	pScreen = SDL_SetVideoMode (ScreenWidth, ScreenHeight, ColorDepth,
                    SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

	if (pScreen == NULL)
	{
        cout << "could not set video mode!" << endl;
        cout << "error message: " << SDL_GetError() << endl;

		SDL_Quit();

		return false;

	}

	return true;
}

/**************************************************************************************************
set back full screen
*/
void CScreen::clearScreen()
{
    SDL_FillRect(pScreen, NULL, SDL_MapRGB (pScreen->format, 10,10,10));
}

/**************************************************************************************************
paint rectangle on screen
*/

void CScreen::paintRect(SDL_Rect Rec, Uint8 R, Uint8 G, Uint8 B)
{
	SDL_FillRect(pScreen, &Rec, SDL_MapRGB(pScreen->format, R ,G ,B));
}

/**************************************************************************************************
flip backbuffer on screen
*/

void CScreen::flipScreen()
{
    SDL_Flip(pScreen);
}

/**************************************************************************************************
runs full screen while the game is running, returns false, if an error occured
*/

bool CScreen::runScreen()
{
	Game.Init(10);

	if (setFullscreen()== false)
	{
		return false;
	}

    SDL_Event Event;
	while (Game.isRunning == true) 
	{
        if (SDL_PollEvent(&Event))
		{
            if (Event.type == SDL_QUIT)
			{
				Game.isRunning = false; 
			}
			else if (Event.type == SDL_KEYDOWN) 
			{
				if (Event.key.keysym.sym == SDLK_ESCAPE)
				Game.isRunning = false; 
			}
		}

		clearScreen();
        Game.Update();
        Game.Control(); //TODO: Control -> Update
		drawGame();
        flipScreen();
	}

    if (!Game.Quit())
    {
        runScreen();
	}

    return true;
}

/**************************************************************************************************
draw snakes and food
*/

void CScreen::drawGame()
{
    //draw snakes
    vector<vector<SDL_Rect>> SnakePos = Game.getSnakePos();
    for (int p = 0; p < SnakePos.size(); p++)
    {
        for (int i = static_cast<int> (SnakePos[p].size())-1 ; i >= 0 ; i--)
        {
            switch(p)
            {
            case 0:
                paintRect(SnakePos[p][i], 0 , 255, 0);
                break;
            case 1:
                paintRect(SnakePos[p][i], 0 , 0, 255);
                break;
            case 2:
                paintRect(SnakePos[p][i], 255 , 255, 0);
                break;
            }
        }
    }

    //draw food:
    for (int i=0; i < Game.getFoodPos().size(); i++)
    {
        paintRect(Game.getFoodPos()[i], 255, 0 , 0);
    }
}

