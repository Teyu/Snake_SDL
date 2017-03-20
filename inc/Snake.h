#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <vector>
#include <string>
#include <array>
using namespace std;

enum direction{up, down, right, left};

class CSnake
{
public:
    CSnake(){ length = 0; d = direction::right; prevD = direction::up; size = 0;}
    void init(uint Px, uint Py, uint len, uint s, direction dir);  //TODO: s?
    void Render();
    void move();
    void changeDirection(int k); //TODO: k? (besser: übergebe direction)
    void grow();
    void destroy();
    vector<SDL_Rect> getPos() const{return Pos;}

    direction getDir() {return d;}
    direction getPrevD() {return prevD;}

protected:
    int length;
	int size; 
    direction d; //TODO: rename dir
    direction prevD; //TODO: rename prevDir
    vector<SDL_Rect> Pos; //TODO: rename
};

bool operator ==(const SDL_Rect &a, const SDL_Rect &b);

#endif
