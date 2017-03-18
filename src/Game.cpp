#include "Game.h"

/**************************************************************************************************
Initialisiert die Membervariablen
*/

void CGame::Init(int res)
{
if (doInit) 
{
	//Initialisiere Spieleranzahl:
	Players = Menu.checkbackPlayers(); //gibt einen Wert im gültigen Bereich zurück

	Names = Menu.checkbackNames(Players);

	//Initialisiere Spieltempo:
	gameTempo = Menu.checkbackTempo();

	Menu.gameStart();
}
//TEST:
isColl = false;
UTurn = false;

	//Initialisiere die Spieler:
	for (int i = 0; i < Players; i++)
	{
		CPlayer P;
		Player.push_back(P);
		Player[i].name = Names[i];
		const int startLength = 5;
		switch (i)
		{
		case 0:  //Spieler 1 startet in der linken oberen Ecke
			Player[i].Init(SDLK_LEFT, SDLK_RIGHT,0,3*res,"right", res); 
			//Er steuert mit den Pfeiltasten links/rechts
			break;
		case 1: //Spieler 2 startet am unteren Bildschirmrand in der Mitte
			Player[i].Init(SDLK_a, SDLK_d, 400-res*startLength, 600-res, "right", res);
			//Er steuert mit A und D
			break;
		case 2: //Spieler 3 startet am rechten Rand in der Mitte 
			Player[i].Init(SDLK_k, SDLK_l,800-res*startLength, 300-res, "left", res);
			//Er steuert mit K und L
			break;
		}
		SPix.push_back(Player[i].getPos());
	} 	
	SnakeTimer = 0.0f;
	for (int i=0; i < Players; i++)
	{
		if (Names[i] == "bot")
		{
			Player[i].setKI(true);
		}
	}


	//Intialisiere die Auflösung
	//Die Auflösung muss ein Teiler von 800 und 600 sein:
	if (((800%res) !=0) || ((600%res) !=0))
	{
		res = 10; //lege ansonsten eine Standardauflösung fest
	} else
	{
		resolution = res;
	}

	//Initialisiere das Futter:
	for (int i=0; i < Players; i++)
	{	
		CFood F;
		Food.push_back(F);
		Food[i].setSize(res);
	}
	spawnFood();
}

/**************************************************************************************************
Updatet den Timer, die Tastatureingaben und die Position von Snake.
*/

void CGame::Update()
{
		//update den Timer:
		timer.update();

		//update die Spieler...
		for (int i = 0; i < Players; i++)
		{
			Player[i].Update();
			if (Player[i].isKI())
			{
				doKI(Player[i]);
			}
		}

		//...und ihre Positionen:
		for (int i = 0; i < Players; i++)
		{
			SPix[i] = Player[i].getPos();
		}
}

/**************************************************************************************************
Bewegt die Schlangen, lässt Snake wachsen, wenn er mit Essen kollidiert,
spawnt neues Essen und beendet das Spiel, wenn Schlangen miteinander kollidieren
*/

void CGame::Control()
{
		//Snake bewegt sich erst, wenn eine gewisse zeit verstrichen ist:
		SnakeTimer += timer.GetElapsed();
		if (SnakeTimer > gameTempo)
		{
			for (int i = 0; i < Players; i++)
			{
				//TEST: 
				if ((UTurn == false) || (Player[i].isKI() == false))
				{
					Player[i].move();
				} else if ((Player[i].isKI()) && (UTurn))
				{
					if (Utimer < 2)
					{
						Player[i].move();
						Utimer++;
					} else
					{
						Player[i].changeDirection(UDir);
						Utimer = 0;
						UTurn = false;
					}
				} //ENDETEST
			}
		 SnakeTimer = 0.0f; 
		}

		//Lasse Snake wachsen, wenn er mit Essen kollidiert:
		//Auch hier ist zu beachten, dass diese Funktion solange aufgerufen wird
		//wie beide kollidieren, daher gibt es eine Variable growLock in der Klasse CPlayer

		for (int i = 0; i< Players; i++)
		{
			for (int j = 0; j < Players; j++)
			{
				if (checkCollFoodSnake(i,j))
				{
					Player[i].growSnake();
					Food[j].destroy();
				}
			}
		}
		spawnFood(); //Danache spawne neues Futter

		//Beende das Spiel, wenn Snake mit sich selbst oder anderen Spielern kollidiert:
		if (checkCollSnakeSnake())
		{
			isRunning = false; 
		}
}

/**************************************************************************************************
Überprüft, ob Snake und Food kollidieren
*/

bool CGame::checkCollFoodSnake(int Plyr, int Foo)
{
	for (int i=0; i < SPix[Plyr].size(); i++)
		{
			if ((SPix[Plyr][i].x == Food[Foo].getPos().x) && (SPix[Plyr][i].y == Food[Foo].getPos().y))
			{
				return true;
			}
		}

	return false;
}

/**************************************************************************************************
Überprüft, ob Snake mit sich selbst oder anderen Spielern kollidiert
*/

bool CGame::checkCollSnakeSnake()
{
	//Die Köpfe der Schlangen:
	vector<SDL_Rect> Heads;
	for (int i = 0; i < Players; i++)
	{
		Heads.push_back(Player[i].getPos()[Player[i].getPos().size() - 1]);
	}

	//Kollidieren Köpfe miteinander?
	if (Players > 1)
	{
		for (int i = 1; i < Players; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if ((Heads[i].x == Heads[j].x) && (Heads[i].y == Heads[j].y))
				{
					return true;
				}
			}
		}
	}

	/*
	for (int pi = 0; pi < Players; pi++)
	{
		for (int p = 0; p < Players; p++) //Kollidiert irgendweiner der Köpfe mit SPieler i?
		{
			for (int i = 0; i < SPix[pi].size() - 1; i++)
			{

				if ((SPix[pi][i].y == Head[p].y) && (SPix[pi][i].x == Head[p].x))
				{
					return true;
				}
			}	
		}
	}*/

	//TEST: eigentlich analog zu oben..
	for (int i = 0; i < Players; i++)
		{
			for (int j = 0; j < Players; j++)
			{
				for (int k=0; k < Player[i].getPos().size()-1; k++)
				{
					if ((Player[i].getPos()[k].x == Heads[j].x) 
						&& (Player[i].getPos()[k].y == Heads[j].y))
					{
						return true;
					}
				}
			}
		} //ENDETEST

	return false;
}

/**************************************************************************************************
Erzeugt Essen an einer zufälligen Position. Dabei wird beachtet, dass diese Position nicht
mit den Schlangen kollidiert.
*/

void CGame::spawnFood()
{
		for (int j = 0; j < Players; j++)
		{
			Food[j].spawn(); 
		}
		for (int i = 0; i < Players; i++)
		{
			for (int j = 0; j < Players; j++)
			{
				while(checkCollFoodSnake(i, j)) //Diese zufällige Position sollte nicht mit Snake kollidieren..
				{
					Food[j].destroy();
					Food[j].spawn(); //..ist das der Fall, erzeuge neu
				}
			}
		}
}

/**************************************************************************************************
Beendet das Spiel und wirft eine Abfrage auf die Konsole, ob man nochmal starten möchte.
Ggf startet das Spiel dann neu
*/

bool CGame::Quit()
{
	SDL_Delay(700); //Wartet die gegebene Zeit in Millisekunden ab bevor es weiter geht
	SDL_Quit(); //Die SDL muss zuvor beendet werden, wenn man mit der Konsoleneingabe arbeiten
				//möchte

	if ((Menu.gameOver(doInit, Player, gameTempo)) == false)
	{
		//alles zurücksetzen:
		for (int i=0; i < Players; i++)
		{
			Player[i].destroy();
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
Gibt die Position des Futters (an den Screen zum zeichnen) zurück
*/

vector<SDL_Rect> CGame::getFoodPos()
{
	vector<SDL_Rect> tmp;
	tmp.push_back(Food[0].getPos());
	for (int i=1; i< Players; i++)
	{
		tmp.push_back(Food[i].getPos());
	}

	return tmp;
}

//Überlade != Operator für Instanzen von CPlayer:
bool operator!=(CPlayer const& lhs, CPlayer const& rhs)
{
	//übliche Implementierung:
	//return ! (lhs==rhs)

	//wenn schon die Längen nicht übereinstimmen können die Spieler nicht gleich sein:
	if (lhs.getPos().size() != rhs.getPos().size())
	{
		return true;
	}

	//teste ob die Positionen übereinstimmen:
	for (int i=0; i < lhs.getPos().size(); i++)
	{
		if ((lhs.getPos()[i].x != rhs.getPos()[i].x) || (lhs.getPos()[i].y != rhs.getPos()[i].y))
		{
			return true;
		}
	}
	return false;
}

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
	case right:
		Headthen.x +=2*resolution;
		Heademerg.x += resolution;
		break;
	case down:
		Headthen.y += 2*resolution;
		Heademerg.y += resolution;
		break;
	case left:
		Headthen.x -= 2*resolution;
		Heademerg.x -= resolution;
		break;
	case up:
		Headthen.y -= 2*resolution;
		Heademerg.y -= resolution;
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
						case right:
							if (actDir == up)
							{
								Bot.changeDirection(SDLK_RIGHT);
							}else
							{
								Bot.changeDirection(SDLK_LEFT);
							}
							break;
						case down:
							if (actDir == left)
							{
								Bot.changeDirection(SDLK_LEFT);
							}else
							{
								Bot.changeDirection(SDLK_RIGHT);
							}
							break;
						case left:
							if (actDir == up)
							{
								Bot.changeDirection(SDLK_LEFT);
							}else
							{
								Bot.changeDirection(SDLK_RIGHT);
							}
							break;
						case up:
							if (actDir == left)
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
						case up:
						case down:
							tmpR.x += resolution;
							tmpL.x -= resolution;
							while(isFull(tmpR) == false)
							{
								tmpR.x += resolution;
								distRight++;
							}
							while(isFull(tmpL) == false)
							{
								tmpL.x -= resolution;
								distLeft++;
							}

							if (distLeft >= distRight)
							{
								if (actDir == up)
								{
									UDir = SDLK_LEFT;
								} else if (actDir == down)
								{
									UDir = SDLK_RIGHT;
								}
							} else if (distRight > distLeft)
							{
								if (actDir == up)
								{
									UDir = SDLK_RIGHT;
								} else if (actDir == down)
								{
									UDir = SDLK_LEFT;
								}
							}

							break;
						case right:
						case left:
							tmpR.y -= resolution;
							tmpL.y += resolution;
							while(isFull(tmpR) == false)
							{
								tmpR.y -= resolution;
								distRight++;
							}
							while (isFull(tmpL) == false)
							{
								tmpL.y += resolution;
								distLeft++;
							}

							
							if (distLeft >= distRight)
							{
								if (actDir == left)
								{
									UDir = SDLK_LEFT;
								} else if (actDir == right)
								{
									UDir = SDLK_RIGHT;
								}
							} else if (distRight > distLeft)
							{
								if (actDir == left)
								{
									UDir = SDLK_RIGHT;
								} else if (actDir == right)
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
		CFood nearest = Food[0]; //Jage dabei das nächstgelegene!
		for (int i = 0; i < Players; i++)
		{
			if ((Players > 1) &&
				(abs(Food[i].getPos().x - Head.x) + abs(Food[i].getPos().y - Head.y) 
				< (abs(nearest.getPos().x - Head.x) + abs(nearest.getPos().y - Head.y))))
			{
				nearest = Food[i];
			}
		}
		goForFood(nearest, Bot); 
	}
}

bool CGame::isFull(SDL_Rect Pix)
{
	//gehe alle Spieler durch:
	for (int p = 0; p < Players; p++)
	{
		//gehe alle Pixel der einzelnen Spieler durch:
		for (int i = 0; i < Player[p].getPos().size(); i++)
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
	case down:
	case up:
	//gehe alle Pixel nach rechts durch
		for (int i = Head.x + resolution; i < 800; i += resolution) 
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
		for (int i = 0; i < Head.x; i += resolution)
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
	case right:
	case left:
	//gehe alle Pixel nach unten durch
		for (int i = Head.y + resolution; i < 600; i += resolution) 
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
		for (int i = 0; i < Head.y; i += resolution)
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
	case down:
	if (side == "right")
	{
	//gehe alle Pixel nach links durch
		for (int i = 0; i < Head.x; i += resolution)
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
		for (int i = Head.x + resolution; i < 800; i += resolution) 
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
	case up: //genauso wie down nur umgekehrt
		if (side == "right")
		{
			//gehe alle Pixel nach rechts durch
			for (int i = Head.x + resolution; i < 800; i += resolution) 
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
			for (int i = 0; i < Head.x; i += resolution)
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
	case right:
		if (side == "right")
		{
			//gehe alle Pixel nach unten durch
			for (int i = Head.y + resolution; i < 600; i += resolution) 
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
			for (int i = 0; i < Head.y; i += resolution)
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
	case left:
		if (side == "right")
		{
			//gehe alle Pixel nach oben durch
			for (int i = 0; i < Head.y; i += resolution)
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
			for (int i = Head.y + resolution; i < 600; i += resolution) 
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
void CGame::goForFood(CFood F, CPlayer& B)
{
	switch(actDir) //ACHTUNG: Dies geht nur, solange es nur einen Bot gibt!!!
	{
	case left:
	case right: //der Bot liegt in waagerechter Position
		//Ziel: ändere die Richtung sobald die xPos  mit der des Essens übereinstimmt
		if (Head.x == F.getPos().x)
		{
			if (Head.y > F.getPos().y)
			//Position des Essens oberhalb
			{
				//Prüfe ob die nächsten 4 Pixel oberhalb frei sind (damit genug Zeit zum ausweichen bleibt)
				//...
				bool isfree = true;
				for (int i = Head.y - 4*resolution; i < Head.y; i += resolution)
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
					if (actDir == right)
					{
						B.changeDirection(SDLK_LEFT);
					} else if (actDir == left)
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
				for (int i = Head.y + resolution; i <= Head.y + 4*resolution ; i += resolution)
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
					if (actDir == right)
					{
						B.changeDirection(SDLK_RIGHT);
					} else if (actDir == left)
					{
						B.changeDirection(SDLK_LEFT);
					}
				}
			}
		}
		break;
	case down:
	case up: //der Bot liegt in senkrechter Position
		//Ziel: ändere die Richtung sobald die yPos  mit der des Essens übereinstimmt
		if (Head.y == F.getPos().y)
		{
			if (Head.x > F.getPos().x)
			//Position des Essens auf linker Seite
			{
				//Prüfe ob die nächsten 4 Pixel links frei sind (damit genug Zeit zum ausweichen bleibt)
				//...
				bool isfree = true;
				for (int i = Head.x - 4*resolution; i < Head.x; i += resolution)
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
					if (actDir == up)
					{
						B.changeDirection(SDLK_LEFT);
					} else if (actDir == down)
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
				for (int i = Head.x + resolution; i <= Head.x + 4*resolution ; i += resolution)
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
					if (actDir == up)
					{
						B.changeDirection(SDLK_RIGHT);
					} else if (actDir == down)
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
