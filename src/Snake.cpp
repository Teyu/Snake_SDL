#include "Snake.h"
#include <iostream>

/**************************************************************************************************
initialize length, size and position of snake
*/
void CSnake::init(uint Px, uint Py, int len, int s, direction dir)
{
    d = dir;
    length = len >= 2 ? len : 2;
    size = s > 0 ? s : 1;

    SDL_Rect Temp;
    Temp.x = Px > 800 - size*length ? 800-size*length : Px;
    Temp.y = Py > 600 - size*length ? 600-size*length : Py;
    Temp.h = size;
    Temp.w = size;

    for (int i=0; i< length; i++)
    {
        Pos.push_back(Temp);
        switch(d)
        {
        case direction::right:
            Temp.x += size;
            break;
        case direction::left:
            Temp.x -= size;
            break;
        case direction::down:
            Temp.y += size;
            break;
        case direction::up:
            Temp.y -= size;
            break;
        }
    }
}

/**************************************************************************************************
move snake by one block in given direction
*/

void CSnake::move()
{
    SDL_Rect Head = Pos[length - 1]; // TODO: remove after m_Head is implemented

    switch (d)
	{
    case direction::right:
        Head.x += size;
        if (Head.x >= 800)
        {
            Head.x = 0;
        }
		break;
    case direction::down:
        Head.y += size;
        if (Head.y >= 600)
        {
            Head.y = 0;
        }
		break;
    case direction::left:
        Head.x -= size;
        if (Head.x < 0)
        {
            Head.x = 800-size;
        }
		break;
    case direction::up:
        Head.y -= size;
        if (Head.y < 0)
        {
            Head.y = 600-size;
        }
		break;
    }

    Pos[length - 1] = Head; // TODO: remove after m_Head

    SDL_Rect prevPos = Pos[length - 1];
    for( int i = length-2; i >= 0; i--)
    {
        SDL_Rect tmp = Pos[i];
        Pos[i] = prevPos;
        prevPos = tmp;
    }
}

//TODO: fortsetzen

/**************************************************************************************************
changes direction of snake to given direction
*/

void CSnake::changeDirection(int k) //TODO : mache zwei funktionen moveLeft und moveRight
{
	prevD = d;
    if ((k == SDLK_RIGHT) || (k == SDLK_l) || (k == SDLK_d))
	{
		switch(d)
		{
        case direction::right:
            d = direction::down;
			break;
        case direction::down:
            d = direction::left;
			break;
        case direction::left:
            d = direction::up;
			break;
        case direction::up:
            d = direction::right;
			break;
		}
	}
	if (((k == SDLK_LEFT) || (k == SDLK_a)) || (k == SDLK_k))
	{
		switch(d)
		{
        case direction::right:
            d = direction::up;
			break;
        case direction::down:
            d = direction::right;
			break;
        case direction::left:
            d = direction::down;
			break;
        case direction::up:
            d = direction::left;
			break;
		}
	}
}

/**************************************************************************************************
snake grows by one block
*/

void CSnake::grow()
{
    SDL_Rect newBlock;
    newBlock = Pos[length-1];

	switch(d)
	{
    case direction::right:
        newBlock.x += size;
		break;
    case direction::down:
        newBlock.y += size;
		break;
    case direction::left:
        newBlock.x -= size;
		break;
    case direction::up:
        newBlock.y -= size;
		break;
	}

    Pos.push_back(newBlock);
	length++;
}

/**************************************************************************************************
destroy snake
*/

void CSnake::destroy()
{
	Pos.clear();
    length = 0;
}
