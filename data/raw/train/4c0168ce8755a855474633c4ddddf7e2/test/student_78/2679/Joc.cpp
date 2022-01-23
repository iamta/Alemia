#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>
#include <time.h>
#include <list>
#include <math.h>

#include "Joc.h"

Game* Game::Instance = NULL;
Game::~Game()
{
	for (auto p : plants)
		delete p;
	for (auto s : seeds)
		delete s;
	for (auto p : projectiles)
		delete p;
	for (auto s : suns)
		delete s;
	for (auto z : zombies)
		delete z;
}
Game::Game()
{
	zombieCount = rand() % 7 + 3;

	UserInterface::ConsoleInput& conIn = UserInterface::ConsoleInput::getInstance();
	//std::string action = conIn.getUserActions()

}

Game& Game::getInstance()
{
	if (Instance == NULL)
		Instance = new Game();
	return *Instance;
}

Game& Game::destroyInstance()
{
	if (Instance != NULL)
		Instance = new Game();
	return *Instance;
}

void Game::ZombieAttack()
{
	if (time % (80000 + rand() % 20000) == 0)
	{
		Zombie* temp(new Zombie(97, 17));
		temp->draw();
		if (zombieCount > 0)
			zombies.push_back(temp);
		else if (zombies.empty()) {
			win = true;
			over = true;
		}
		zombieCount--;
	}
}


void Game::CreateMap()
{
	for (int i = 10; i <= 100; i += 10)
	{
		for (int j = 5; j <= 30; j += 5)
		{
			Casuta s;
			s.Start.x = i; s.Start.y = j;
			s.End.x = i + 10; s.End.y = j + 5;

			tabel.push_back(s);
		}
	}
	for (int i = 5; i <= 30; i++)
	{
		for (int j = 10; j <= 100; j++)
		{
			if (i % 5 == 0)
				conOut(j, i) << (((i + j) % 2) ? ':' : '.');

			if (j % 10 == 0)
				conOut(j, i) << ':';
		}
	}
	seeds.push_back(new Peashooter(3, 7));
	seeds.push_back(new SunFlower(3, 12));

	for (auto i : seeds)
	{
		i->draw();
	}

}

void Game::createSun()
{
	if (time++ % (30000 + rand() % 10000) == 0)
	{
		suns.push_back(Sun::SunFactory());
	}
}

void Game::plant(Plant* seed)
{
	UserInterface::ConsoleInput& conIn = UserInterface::ConsoleInput::getInstance();

	for (auto t : tabel)
	{
		coord c{ conIn.getX(),conIn.getY() };
		if (t.apartenenta(c))
		{
			Plant* p = seed->clone();
			p->setX(t.Start.x + 2);
			p->setY(t.Start.y + 2);
			p->draw();

			Sun::addSun(-p->getCost());
			plants.push_back(p);
		}
	}
}

void Game::checkPlant()
{
	UserInterface::ConsoleInput& conIn = UserInterface::ConsoleInput::getInstance();

	static Plant* toBePlanted = NULL;

	if (conIn.getY() >= 5)
		//if (action.find("double") != std::string::npos)
	{
		if (toBePlanted == NULL)
		{
			if (conIn.getX() <= 9 && conIn.getY() >= 5)
			{
				for (auto s : seeds) {
					if (conIn.getY() <= s->gety() + 3 && conIn.getY() > s->gety() - 2 && Sun::getSunCounter() >= s->getCost())
					{
						toBePlanted = s;
						conOut(s->getx(), s->gety() + 2) << "^^^";
						return;
					}
				}
			}
		}
		else
		{
			conOut(toBePlanted->getx(), toBePlanted->gety() + 2) << "   ";
			plant(toBePlanted);
			toBePlanted = NULL;
		}
	}
}

void Game::checkSun()
{
	UserInterface::ConsoleInput& conIn = UserInterface::ConsoleInput::getInstance();

	//std::string action = conIn.getUserActions();

	//if (action.find("double") != std::string::npos)
	{
		for (auto it = suns.begin(); it != suns.end(); it++)
		{
			if (abs(conIn.getX() - (*it)->getX()) <= 5 && abs(conIn.getY() - (*it)->getY() <= 3))
			{
				delete (*it);
				suns.remove(*it);
				Sun::addSun(50);
				break;
			}
		}
	}
}

