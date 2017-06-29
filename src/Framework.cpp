#include "Framework.h"

/****************************************************************************************************************************************************
initialise
*/

bool CRealFramework::Init(int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen) //TODO: remove bFullScreen
{
    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
    {
        cout << "could not initialize SDL!" << endl;
        cout << "error message: " << SDL_GetError () << endl;
        SDL_Quit();

        return false;
    }

    m_ScreenW = ScreenWidth;
    m_ScreenH = ScreenHeight;

    if (!setFullscreen())
    {
        return false;
    }

    m_pKeystate = SDL_GetKeyState(NULL);

	return true;
}

/**************************************************************************************************
generates a full screen, return true when succeeded otherwise false
*/
bool CRealFramework::setFullscreen() //TODO: Hand over colordepth (see above)
{
    int ColorDepth = 16;

    m_pScreen = SDL_SetVideoMode (m_ScreenW, m_ScreenH, ColorDepth,
                    SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

    if (m_pScreen == NULL)
    {
        cout << "could not set video mode!" << endl;
        cout << "error message: " << SDL_GetError() << endl;

        SDL_Quit();

        return false;

    }

    return true;
}

/****************************************************************************************************************************************************
shut down framework
*/

void CRealFramework::Quit()
{
	SDL_Quit();
    g_pTimer->Del();
}

/****************************************************************************************************************************************************
update framework
*/

void CRealFramework::Update()
{
    g_pTimer->update();
	SDL_PumpEvents();
}

/****************************************************************************************************************************************************
verify if a certain key is pressed
*/

bool CRealFramework::KeyDown( int Key_ID)
{
	return (m_pKeystate[Key_ID] ? true : false);
}

/****************************************************************************************************************************************************
clear framework
*/

void CRealFramework::Clear()
{
    SDL_FillRect (m_pScreen, NULL, SDL_MapRGB (m_pScreen->format, 0, 0, 0));
}

/****************************************************************************************************************************************************
display on screen
*/

void CRealFramework::Flip()
{
	SDL_Flip(m_pScreen);
}

/****************************************************************************************************************************************************
copies image to screen
*/

void CRealFramework::BlitSurface( SDL_Surface &Image, SDL_Rect &Rect)
{
    //TODO: prüfe vorher, dass m_pImage, m_pScreen gesetzt sind, sonst werfe Error
    SDL_BlitSurface(&Image, NULL, m_pScreen, &Rect);
}

/**************************************************************************************************
paint rectangle on screen
*/

void CRealFramework::paintRect(SDL_Rect Rec, Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(m_pScreen, &Rec, SDL_MapRGB(m_pScreen->format, R ,G ,B));
}

/**************************************************************************************************
draw snakes and food
*/

void CRealFramework::drawScene(vector<vector<SDL_Rect>> &SnakePos, vector<SDL_Rect> &FoodPos)
{
    //draw snakes
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
}
