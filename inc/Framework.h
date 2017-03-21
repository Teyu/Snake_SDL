#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include <sstream>
#include <vector>
#include "Singleton.h"
#include "Timer.h"

using namespace std;

#define g_pFramework CFramework::Get() //pointer to single entity of CFramework

class CFramework : public TSingleton<CFramework>
{
public:
    virtual bool Init (int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen);
    virtual void Quit();
    virtual void Update();
    virtual void drawScene(vector<vector<SDL_Rect>> &SnakePos, vector<SDL_Rect> &FoodPos);
    virtual void Clear();
    virtual void Flip();
    virtual bool KeyDown( int Key_ID);
    virtual SDL_Surface *GetScreen() { return m_pScreen;}
    int GetScreenWidth() { return m_ScreenW;} //TODO: kann man diese auch über SDL_Surface abfragen?
    int GetScreenHeight() { return m_ScreenH;}

private:
    void paintRect(SDL_Rect Rec, Uint8 R, Uint8 G, Uint8 B);
    bool setFullscreen();

private:
    SDL_Surface *m_pScreen;
    CTimer m_timer;
    Uint8 *m_pKeystate;
    int m_ScreenW;
    int m_ScreenH;
};

#endif
