#ifndef SNAKE_H
	#define SNAKE_H

#include <SDL.h>
#include <vector>
#include <string>
#include <array>
using namespace std;

class CSnake
{
public:
	CSnake(){ length = 0; d = right; prevD = up; size = 0;} //Konstruktor
	void init(int Px, int Py, int len, int s, string dir); 
	void move(); 
	void changeDirection(int k);
	void grow();
	void destroy();
	vector<SDL_Rect> getPos() const{return Pos;} 

	enum direction{up, down, right, left};
	direction getDir() {return d;}
	direction getPrevD() {return prevD;}

protected:
	int length;

private: 
	int size; 
	direction d;
	direction prevD;
	vector<SDL_Rect> Pos;
};

#endif