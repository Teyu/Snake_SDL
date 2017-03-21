#ifndef SPRITE_H
#define SPRITE_H

#include "Framework.h"

class CSprite
{
public: 
    CSprite();
    CSprite(const CSprite& newSprite) :
            m_pScreen(newSprite.m_pScreen), m_pImage(newSprite.m_pImage), m_Rect(newSprite.m_Rect), m_sImageFile(newSprite.m_sImageFile)
        {}
    CSprite& operator= (const CSprite& other){
        std::cout << "operator=" << std::endl;
        if (this != &other) {
            m_pScreen = other.m_pScreen;
            m_pImage = other.m_pImage;
            m_Rect = other.m_Rect;
            m_sImageFile = other.m_sImageFile;
        }
        return *this;
    }
    ~CSprite();

    void Load (const string sFilename);
	
    void SetPos(float fXPos, float fYPos);
    void Render();
    SDL_Rect GetRect() const {return m_Rect;}

private:
    SDL_Surface *m_pScreen;
    SDL_Surface *m_pImage;
    SDL_Rect m_Rect;
    string m_sImageFile;
};


#endif
