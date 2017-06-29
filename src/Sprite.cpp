#include "Sprite.h"

/****************************************************************************************************************************************************
destructor
*/

CSprite::~CSprite()
{
    SDL_FreeSurface (m_pImage);
    m_pImage = NULL;
}

/****************************************************************************************************************************************************
load an image file
*/

void CSprite::Load( const string sFilename)
{
	m_sImageFile = sFilename;

    m_pImage = SDL_LoadBMP( sFilename.c_str() );

    if (m_pImage == NULL)
	{
        cout << "An error occured loading the following file: " << sFilename.c_str();
		cout << endl;
        cout << "Error message: " << SDL_GetError() << endl;

        m_pFramework->Quit();
		exit(1);
    }

    //TODO: nur bei bereits ungültiger position: (sonst wird gültige überschrieben)
	m_Rect.x = -1; //this way an exception will be thrown if position hasn't been set 
	m_Rect.y = -1;
    m_Rect.w = m_pImage->w;
    m_Rect.h = m_pImage->h;
}

/****************************************************************************************************************************************************
set the position (negative positions allowed)
*/

void CSprite::SetPos( float fXPos, float fYPos)
{
	//sprite moves only when next integer is exceeded. This way its easier to control the speed of movement 
	m_Rect.x = static_cast<int>(fXPos);
    m_Rect.y = static_cast<int>(fYPos);
}

/****************************************************************************************************************************************************
render  (caution: framework has to be initialized!)
*/

void CSprite::Render()
{
    if ((m_Rect.x < 0) || (m_Rect.y < 0))
    {
        throw "could not render sprite: invalid position";
    }

    //TODO: prüfe vorher, dass m_pImage gesetzt ist, sonst werfe Error
    m_pFramework->BlitSurface(*m_pImage, m_Rect);
}
