#include "Game.h"

/**************************************************************************************************
initialize member variables
*/

void CGame::Init(int resolution)
{
    if (doInit)
    {
        Players = Menu->checkbackPlayers(); //TODO: checkbackPlayers should return std::vector<CPlayer>
        Names = Menu->checkbackNames(Players); //TODO: can be removed than
        gameTempo = Menu->checkbackTempo();

        Menu->gameStart();
    }

    isColl = false;
    UTurn = false;

    //TODO: s.o.
    Player.resize(Players);
	for (int i = 0; i < Players; i++)
	{
        Player[i] = new CPlayer(*Framework);
        Player[i]->name = Names[i];
        //TODO: new function: setupStartPositions
		const int startLength = 5;
		switch (i)
		{
		case 0:  //Spieler 1 startet in der linken oberen Ecke
            Player[i]->Init(SDLK_LEFT, SDLK_RIGHT,0,3*resolution, direction::right, resolution);
			//Er steuert mit den Pfeiltasten links/rechts
			break;
		case 1: //Spieler 2 startet am unteren Bildschirmrand in der Mitte
            Player[i]->Init(SDLK_a, SDLK_d, 400-resolution*startLength, 600-resolution, direction::right, resolution);
			//Er steuert mit A und D
			break;
		case 2: //Spieler 3 startet am rechten Rand in der Mitte 
            Player[i]->Init(SDLK_k, SDLK_l,800-resolution*startLength, 300-resolution, direction::left, resolution);
			//Er steuert mit K und L
			break;
		}
        SPix.push_back(Player[i]->getPos()); //TODO: wird SPix benötigt?
	} 	
    SnakeTimer = 0.0f;
	for (int i=0; i < Players; i++)
	{
		if (Names[i] == "bot")
		{
            Player[i]->setKI(true); //TODO: wenn CBot von CSnake erbt können CPlayer und CBot beide als CSnakes behandelt werden (Polymorphie)
		}
    }


    // TODO: new function setResolution
    // TODO: remove magic numbers 800 und 600
    if (((800%resolution) !=0) || ((600%resolution) !=0))
	{
        m_resolution = 10;
	} else
	{
        m_resolution = resolution;
	}

    // TODO: new function initFood
    Food.resize(Players);
	for (int i=0; i < Players; i++)
    {
        Food[i] = new CFood(*Framework);
        Food[i]->setSize(resolution);
	}
    spawnFood();

    Framework->Init(800, 600, 16, false);
    isRunning = true; //TODO: umbennenen (misleading)
}

/**************************************************************************************************
render Scene
*/

void CGame::Render()
{
    for (size_t i = 0; i < Food.size(); i++)
        Food[i]->Render();
}

/****************************************************************************************************************************************************
verify if a button is pressed to quit the game
*/

void CGame::ProcessEvents()
{
    if (Framework->KeyDown(SDLK_ESCAPE))
    {
        isRunning = false;
        return;
    }

    SDL_Event Event;
    if (SDL_PollEvent ( &Event))
    {
        switch(Event.type)
        {
        case (SDL_QUIT):
            {
                isRunning = false;
            } break;
        }
    }
}

void CGame::Run()
{
    if (!isRunning)
        isRunning = true;

    ProcessEvents();

    Framework->Update();
    Framework->Clear();

    Update();

    Control(); //TODO: Control -> Update
    vector<vector<SDL_Rect>> SnakePos = getSnakePos();
    vector<SDL_Rect> FoodPos = getFoodPos();

    Framework->drawScene(SnakePos, FoodPos); //TODO: warum funktioniert das nicht direkt?

    Render();
    Framework->Flip();

    if (!isRunning)
    {
        Quit();
        if (!isGameOver())
        {
            Init(10);
        }
    }
}

/**************************************************************************************************
updates the timer, the keyboard input and the position of the Snakes
*/

void CGame::Update()
{
        for (int i = 0; i < Players; i++)
		{
            Player[i]->Update();
            if (Player[i]->isKI()) // TODO: can be removed, wenn CBot : CSnake
            {
                doKI(*Player[i]);
			}
		}

		for (int i = 0; i < Players; i++)
        {
            SPix[i] = Player[i]->getPos(); // TODO. nicht notwendig
        }
}

/**************************************************************************************************
coordinates the Players' movements
*/

void CGame::Control()
{
        SnakeTimer += g_pTimer->GetElapsed();
		if (SnakeTimer > gameTempo)
		{
            //TEST:
            for (int i = 0; i < Players; i++)
            {
                if ((UTurn == false) || (Player[i]->isKI() == false))
                {
                    Player[i]->move();
                } else if ((Player[i]->isKI()) && (UTurn))
				{
                    if (Utimer < 2)
					{
                        Player[i]->move();
						Utimer++;
					} else
					{
                        Player[i]->changeDirection(UDir);
						Utimer = 0;
						UTurn = false;
                    }
                }
            }
            //ENDETEST
        SnakeTimer = 0.0f;
        }

		for (int i = 0; i< Players; i++)
		{
			for (int j = 0; j < Players; j++)
			{
                if (checkCollFoodSnake(i,j)) //TODO: rename checkColl(CFood, CSnake)
				{
                    Player[i]->growSnake();
                    Food[j]->destroy();
                    spawnFood();
				}
			}
        }

        if (checkCollSnakeSnake()) //TODO: rename: checkColl(CSnake, CSnake) and move into loop above
		{
			isRunning = false; 
        }
}

/**************************************************************************************************
checks collision of snake and food
*/

bool CGame::checkCollFoodSnake(int Plyr, int Foo)
{
    for (int i=0; i < SPix[Plyr].size(); i++) //TODO : replace SPix with actual function call
		{
            if ((SPix[Plyr][i].x == Food[Foo]->getPos().x) && (SPix[Plyr][i].y == Food[Foo]->getPos().y))
			{
				return true;
			}
		}

	return false;
}

/**************************************************************************************************
checks collision of snake with itself or other snakes
*/

bool CGame::checkCollSnakeSnake()
{
    vector<SDL_Rect> Heads; //TODO: ertselle membervariable in CSnake m_Head -> then remove:
	for (int i = 0; i < Players; i++)
	{
        Heads.push_back(Player[i]->getPos()[Player[i]->getPos().size() - 1]);
	}

    for (int i = 0; i < Players; i++) //TODO: foreach schleife für bessere lesbarkeit ?
    {
        for (int j = 0; j < Players; j++)
        {
             for (int k = 0; k < Player[i]->getPos().size(); k++)
             {
                if ((Player[i]->getPos()[k].x == Heads[j].x)
                    && (Player[i]->getPos()[k].y == Heads[j].y)) //TODO: überlade ==operator für Rect
                {
                    if (i == j) //its own Head
                        break;
                    return true;
                }
            }
        }
    }

	return false;
}

/**************************************************************************************************
spawns new food at a random "empty" place on screen. The new position is not colliding with any snake
*/

void CGame::spawnFood()
{
        for (int i = 0; i < Players; i++) //TODO: foreach schleife für bessere lesbarkeit
		{
            Food[i]->spawn();
			for (int j = 0; j < Players; j++)
			{
                while(checkCollFoodSnake(i, j))
				{
                    Food[j]->destroy();
                    Food[j]->spawn();
				}
			}
        }
}

/**************************************************************************************************
quits the game, opens the menu and restarts the game or shuts it down based on the users input.
Returns true if the user wants to end the game, otherwise returns false
*/

void CGame::Quit()
{
    SDL_Delay(700);
    SDL_Quit();
}

bool CGame::isGameOver()
{
    if (!(Menu->gameOver(doInit, Player, gameTempo))) //TODO: rename -> gameover is misleading
    {
        for (int i=0; i < Players; i++)
        {
            Player[i]->destroy();
            free(Player[i]);
            free(Food[i]);
        }
        Food.clear();
        Player.clear();
        SPix.clear();

        isRunning = true;

        return false;
    } else
    {
        isRunning = false;
        return true;
    }
}

/**************************************************************************************************
returns the position of the food (usually to draw on screen)
*/

vector<SDL_Rect> CGame::getFoodPos()
{
    vector<SDL_Rect> ret;
    for (int i=0; i< Players; i++)
	{
        ret.push_back(Food[i]->getPos());
	}

    return ret;
}

//TODO: move to public interface of CSnake:
bool operator!=(CPlayer const& lhs, CPlayer const& rhs)
{
    if (lhs.getPos().size() != rhs.getPos().size()) //TODO: CSnake::getLength
	{
		return true;
	}

	for (int i=0; i < lhs.getPos().size(); i++)
	{
		if ((lhs.getPos()[i].x != rhs.getPos()[i].x) || (lhs.getPos()[i].y != rhs.getPos()[i].y))
		{
			return true;
		}
	}
	return false;
}

//TODO: move to CBot:

//gibt true zurück, wenn der Bot seine Richtung aufgrund von Kollision ändern muss
void CGame::doKI( CPlayer &Bot)
{
	//Julias KI
	//Ohne Früchte
	const int ScreenWidth = 800;
	const int ScreenHeight = 600;

	//Kopf der Schlange:
	Head = Bot.getPos()[Bot.getPos().size() - 1];

	//aktuelle Richtung:
	actDir = static_cast<direction>(Bot.getDir());

	//vorige Richtung:
	prevDir = static_cast<direction>(Bot.getPrevD());

	//Position des Kopfes in zwei Zügen:
	Headthen = Head;
	//Position des Kopfes in einem Zug: Notausweichen
	Heademerg = Head;

	switch(actDir)
	{
    case direction::right:
        Headthen.x +=2*m_resolution;
        Heademerg.x += m_resolution;
		break;
    case direction::down:
        Headthen.y += 2*m_resolution;
        Heademerg.y += m_resolution;
		break;
    case direction::left:
        Headthen.x -= 2*m_resolution;
        Heademerg.x -= m_resolution;
		break;
    case direction::up:
        Headthen.y -= 2*m_resolution;
        Heademerg.y -= m_resolution;
		break;
	}

	//b) Kollision mit einem Mitspieler oder sich selbst in 2 Zügen:
	for (int pi = 0; pi < Players; pi++)
	{
			for (int i = 0; i < SPix[pi].size(); i++)
			{
				if (((SPix[pi][i].y == Headthen.y) && (SPix[pi][i].x == Headthen.x))
					|| ((SPix[pi][i].y == Heademerg.y) && (SPix[pi][i].x == Heademerg.x)))
				{
					//KOLLISION 
				
					//b.1) Zur Linken und Rechten ist frei 
					if (isFreeBothSides() && (isColl == false)) 
					{
						//Anweisung:
						//bewege dich in die entgegengesetzte Richtung zur vorigen: ZTurn
						switch (prevDir)
						{
                        case direction::right:
                            if (actDir == direction::up)
							{
								Bot.changeDirection(SDLK_RIGHT);
							}else
							{
								Bot.changeDirection(SDLK_LEFT);
							}
							break;
                        case direction::down:
                            if (actDir == direction::left)
							{
								Bot.changeDirection(SDLK_LEFT);
							}else
							{
								Bot.changeDirection(SDLK_RIGHT);
							}
							break;
                        case direction::left:
                            if (actDir == direction::up)
							{
								Bot.changeDirection(SDLK_LEFT);
							}else
							{
								Bot.changeDirection(SDLK_RIGHT);
							}
							break;
                        case direction::up:
                            if (actDir == direction::left)
							{
								Bot.changeDirection(SDLK_RIGHT);
							} else
							{
								Bot.changeDirection(SDLK_LEFT);
							}
							break;
						}
						//isColl = true; //Es sollte gnügen dies einmal am ende des if-Blocks zu tun
					}

					//b.2) Nur eine Seite ist frei: 
					else if (isFreeOneSide("right") && (isColl == false))
					{
						//Anweisung:
						//gehe zu freien Seite
						Bot.changeDirection(SDLK_RIGHT);
						//isColl = true;
					} else if (isFreeOneSide("left") && (isColl == false))
					{
						//Anweisung:
						//gehe zur freien Seite
						Bot.changeDirection(SDLK_LEFT);
						//isColl = true;
					}

					//b.3) Beide Seiten nicht frei: (Und er ist gerade nicht bei einem UTurnmanöver)
					else if ((isNotFreeBothSides()) && (UTurn ==false))
					{
						//Anweisung:
						//mache einen U-Turn in die Richtung, wo mehr Platz ist:
						int distRight = 0;
						int distLeft = 0;
						SDL_Rect tmpR = Head;
						SDL_Rect tmpL = Head;

						Utimer = 0;
						UTurn = true;

						switch (actDir)
						{
                        case direction::up:
                        case direction::down:
                            tmpR.x += m_resolution;
                            tmpL.x -= m_resolution;
							while(isFull(tmpR) == false)
							{
                                tmpR.x += m_resolution;
								distRight++;
							}
							while(isFull(tmpL) == false)
							{
                                tmpL.x -= m_resolution;
								distLeft++;
							}

							if (distLeft >= distRight)
							{
                                if (actDir == direction::up)
								{
									UDir = SDLK_LEFT;
                                } else if (actDir == direction::down)
								{
									UDir = SDLK_RIGHT;
								}
							} else if (distRight > distLeft)
							{
                                if (actDir == direction::up)
								{
									UDir = SDLK_RIGHT;
                                } else if (actDir == direction::down)
								{
									UDir = SDLK_LEFT;
								}
							}

							break;
                        case direction::right:
                        case direction::left:
                            tmpR.y -= m_resolution;
                            tmpL.y += m_resolution;
							while(isFull(tmpR) == false)
							{
                                tmpR.y -= m_resolution;
								distRight++;
							}
							while (isFull(tmpL) == false)
							{
                                tmpL.y += m_resolution;
								distLeft++;
							}

							
							if (distLeft >= distRight)
							{
                                if (actDir == direction::left)
								{
									UDir = SDLK_LEFT;
                                } else if (actDir == direction::right)
								{
									UDir = SDLK_RIGHT;
								}
							} else if (distRight > distLeft)
							{
                                if (actDir == direction::left)
								{
									UDir = SDLK_RIGHT;
                                } else if (actDir == direction::right)
								{
									UDir = SDLK_LEFT;
								}
							}

							break;
						}
						Bot.changeDirection(UDir);

						//isColl = true;
					}

				//TEST
				isColl = true;

				} else if (UTurn == false)
				{
					isColl = false;
				}
			}	
	}

	if (isColl == false)
    {
		//Wenn die Gefahr einer Kollision nicht besteht, 
		//lasse den Bot auf Futtersuche gehen:
        CFood *nearest = Food[0]; //Jage dabei das nächstgelegene!
		for (int i = 0; i < Players; i++)
		{
			if ((Players > 1) &&
                (abs(Food[i]->getPos().x - Head.x) + abs(Food[i]->getPos().y - Head.y)
                < (abs(nearest->getPos().x - Head.x) + abs(nearest->getPos().y - Head.y))))
			{
                nearest = Food[i];
			}
		}
        goForFood(*nearest, Bot);

    }
}

bool CGame::isFull(SDL_Rect Pix)
{
	//gehe alle Spieler durch:
	for (int p = 0; p < Players; p++)
	{
		//gehe alle Pixel der einzelnen Spieler durch:
        for (int i = 0; i < Player[p]->getPos().size(); i++)
		{
			if ((SPix[p][i].x == Pix.x) && (SPix[p][i].y == Pix.y))
			{
				return true;
			}
		}
	}
	return false;
}

bool CGame::isFreeBothSides()
{
	switch(actDir)
	{
    case direction::down:
    case direction::up:
	//gehe alle Pixel nach rechts durch
        for (int i = Head.x + m_resolution; i < 800; i += m_resolution)
		{
		//frage ab, ob eine Pixel-Position auf der rechten Seite besetzt ist:
			SDL_Rect tmp = Head;
			tmp.x = i;
			if (isFull(tmp))
			{
				//Zur Rechten ist nicht frei
				//cout << "Zur rechten ist nicht frei!" << endl;
				//cout << "An Position x : " << i << endl;
				return false;
			}
		}
	//gehe alle Pixel nach links durch
        for (int i = 0; i < Head.x; i += m_resolution)
		{
			SDL_Rect tmp = Head;
			tmp.x = i;
			if (isFull(tmp))
			{
				//Zur Linken ist nicht frei
				//cout << "Zur linken ist nicht frei!" << endl;
				//cout << "An Position x : " << i << endl;
				return false;
			}
		}
		break;
    case direction::right:
    case direction::left:
	//gehe alle Pixel nach unten durch
        for (int i = Head.y + m_resolution; i < 600; i += m_resolution)
		{
			SDL_Rect tmp = Head;
			tmp.y = i;
			if (isFull(tmp))
			{
				//Nach unten ist nicht frei
				//cout << "Nach unten ist nicht frei!" << endl;
				//cout << "An Position y : " << i << endl;
				return false;
			}
		}
	//gehe alle Pixel nach oben durch
        for (int i = 0; i < Head.y; i += m_resolution)
		{
			SDL_Rect tmp = Head;
			tmp.y = i;
			if (isFull(tmp))
			{
				//Nach oben ist nicht frei
				//cout << "Nach oben ist nicht frei!" << endl;
				//cout << "An Position y : " << i << endl;
				return false;
			}
		}
		break;
	}
	return true;
}

bool CGame::isFreeOneSide(string side)
{
	switch(actDir)
	{
    case direction::down:
	if (side == "right")
	{
	//gehe alle Pixel nach links durch
        for (int i = 0; i < Head.x; i += m_resolution)
		{
			SDL_Rect tmp = Head;
			tmp.x = i;
			if (isFull(tmp))
			{
				return false;
			}
		}
	} else if (side == "left")
	{
		//gehe alle Pixel nach rechts durch
        for (int i = Head.x + m_resolution; i < 800; i += m_resolution)
		{
		//frage ab, ob eine Pixel-Position auf der rechten Seite besetzt ist:
			SDL_Rect tmp = Head;
			tmp.x = i;
			if (isFull(tmp))
			{
				return false;
			}
		}
	}
		break;
    case direction::up: //genauso wie down nur umgekehrt
		if (side == "right")
		{
			//gehe alle Pixel nach rechts durch
            for (int i = Head.x + m_resolution; i < 800; i += m_resolution)
			{
			//frage ab, ob eine Pixel-Position auf der rechten Seite besetzt ist:
				SDL_Rect tmp = Head;
				tmp.x = i;
				if (isFull(tmp))
				{
					return false;
				}
			}
			} else if (side == "left")
			{
			//gehe alle Pixel nach links durch
            for (int i = 0; i < Head.x; i += m_resolution)
			{
				SDL_Rect tmp = Head;
				tmp.x = i;
				if (isFull(tmp))
				{
					return false;
				}
			}
			}
			break;
    case direction::right:
		if (side == "right")
		{
			//gehe alle Pixel nach unten durch
            for (int i = Head.y + m_resolution; i < 600; i += m_resolution)
			{
				SDL_Rect tmp = Head;
				tmp.y = i;
				if (isFull(tmp))
				{
					return false;
				}
			}
		} else if (side == "left")
		{
			//gehe alle Pixel nach oben durch
            for (int i = 0; i < Head.y; i += m_resolution)
			{
				SDL_Rect tmp = Head;
				tmp.y = i;
				if (isFull(tmp))
				{
					return false;
				}
			}
		}
		break;
    case direction::left:
		if (side == "right")
		{
			//gehe alle Pixel nach oben durch
            for (int i = 0; i < Head.y; i += m_resolution)
			{
				SDL_Rect tmp = Head;
				tmp.y = i;
				if (isFull(tmp))
				{
					return false;
				}
			}
		} else if (side == "left")
		{
			//gehe alle Pixel nach unten durch
            for (int i = Head.y + m_resolution; i < 600; i += m_resolution)
			{
				SDL_Rect tmp = Head;
				tmp.y = i;
				if (isFull(tmp))
				{
					return false;
				}
			}
		}
		break;
	}
	return true;
}

//ZUM TESTEN: EINZELSPIELER BOT
void CGame::goForFood(CFood &F, CPlayer& B)
{
	switch(actDir) //ACHTUNG: Dies geht nur, solange es nur einen Bot gibt!!!
	{
    case direction::left:
    case direction::right: //der Bot liegt in waagerechter Position
		//Ziel: ändere die Richtung sobald die xPos  mit der des Essens übereinstimmt
		if (Head.x == F.getPos().x)
		{
			if (Head.y > F.getPos().y)
			//Position des Essens oberhalb
			{
				//Prüfe ob die nächsten 4 Pixel oberhalb frei sind (damit genug Zeit zum ausweichen bleibt)
				//...
				bool isfree = true;
                for (int i = Head.y - 4*m_resolution; i < Head.y; i += m_resolution)
				{
					SDL_Rect tmp = Head;
					tmp.y = i;
					if (isFull(tmp))
					{
						isfree = false;
					}
				}
				//...und ändere die Richtung, wenn das der Fall ist:
				if (isfree)
				{
                    if (actDir == direction::right)
					{
						B.changeDirection(SDLK_LEFT);
                    } else if (actDir == direction::left)
					{
						B.changeDirection(SDLK_RIGHT);
					}
				}
			} else if (Head.y < F.getPos().y)
			//Position des Essens unterhalb
			{
				//Prüfe ob die nächsten 4 Pixel unterhalb frei sind (damit genug Zeit zum ausweichen bleibt)
				//...
				bool isfree = true;
                for (int i = Head.y + m_resolution; i <= Head.y + 4*m_resolution ; i += m_resolution)
				{
					SDL_Rect tmp = Head;
					tmp.y = i;
					if (isFull(tmp))
					{
						isfree = false;
					}
				}
				//...und ändere die Richtung, wenn das der Fall ist:
				if (isfree)
				{
                    if (actDir == direction::right)
					{
						B.changeDirection(SDLK_RIGHT);
                    } else if (actDir == direction::left)
					{
						B.changeDirection(SDLK_LEFT);
					}
				}
			}
		}
		break;
    case direction::down:
    case direction::up: //der Bot liegt in senkrechter Position
		//Ziel: ändere die Richtung sobald die yPos  mit der des Essens übereinstimmt
		if (Head.y == F.getPos().y)
		{
			if (Head.x > F.getPos().x)
			//Position des Essens auf linker Seite
			{
				//Prüfe ob die nächsten 4 Pixel links frei sind (damit genug Zeit zum ausweichen bleibt)
				//...
				bool isfree = true;
                for (int i = Head.x - 4*m_resolution; i < Head.x; i += m_resolution)
				{
					SDL_Rect tmp = Head;
					tmp.x = i;
					if (isFull(tmp))
					{
						isfree = false;
					}
				}
				//...und ändere die Richtung, wenn das der Fall ist:
				if (isfree)
				{
                    if (actDir == direction::up)
					{
						B.changeDirection(SDLK_LEFT);
                    } else if (actDir == direction::down)
					{
						B.changeDirection(SDLK_RIGHT);
					}
				}
			} else if (Head.x < F.getPos().x)
			//Position des Essens auf rechter Seite
			{
				//Prüfe ob die nächsten 4 Pixel rechts frei sind (damit genug Zeit zum ausweichen bleibt)
				//...
				bool isfree = true;
                for (int i = Head.x + m_resolution; i <= Head.x + 4*m_resolution ; i += m_resolution)
				{
					SDL_Rect tmp = Head;
					tmp.x = i;
					if (isFull(tmp))
					{
						isfree = false;
					}
				}

				//...und ändere die Richtung, wenn das der Fall ist:
				if (isfree)
				{
                    if (actDir == direction::up)
					{
						B.changeDirection(SDLK_RIGHT);
                    } else if (actDir == direction::down)
					{
						B.changeDirection(SDLK_LEFT);
					}
				}
			}
		}
		break;
	}
}

bool CGame::isNotFreeBothSides()
{
	if ((isFreeOneSide("left") == false) && (isFreeOneSide("right") == false))
	{
		return true;
	}
	return false;
}
