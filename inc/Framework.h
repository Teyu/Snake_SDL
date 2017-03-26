#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <iostream>
#include <sstream>
#include <vector>
#include "Singleton.h"
#include "Timer.h"

using namespace std;

#define g_pFramework CRealFramework::Get() //TODO: Singleton abschaffen

class CFramework
{
public:
    virtual ~CFramework() {}
    virtual bool Init (int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen) = 0;
    virtual void Quit() = 0;
    virtual void Update() = 0;
    virtual void drawScene(vector<vector<SDL_Rect>> &SnakePos, vector<SDL_Rect> &FoodPos) = 0;
    virtual void Clear() = 0;
    virtual void Flip() = 0;
    virtual bool KeyDown( int Key_ID) = 0;
    virtual void BlitSurface( SDL_Surface &Image, SDL_Rect &Rect) = 0;
};

class CRealFramework : public CFramework, public TSingleton<CRealFramework>
{
public:
    ~CRealFramework() {}
    bool Init (int ScreenWidth, int ScreenHeight, int ColorDepth, bool bFullscreen);
    void Quit();
    void Update();
    void drawScene(vector<vector<SDL_Rect>> &SnakePos, vector<SDL_Rect> &FoodPos);
    void Clear();
    void Flip();
    bool KeyDown( int Key_ID);
    void BlitSurface( SDL_Surface &Image, SDL_Rect &Rect);
    SDL_Surface *GetScreen() { return m_pScreen;}
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
