#include "Pea.h"
#include "ConsoleOutput.h"
#include "Joc.h"

Pea::~Pea()
{
	UserInterface::ConsoleOutput::getInstance()(x, y) << " ";
}

void Pea::move()
{
	Game& game = Game::getInstance();

	UserInterface::ConsoleOutput::getInstance()(x, y) << " ";	

	for (auto p : game.plants)
	{
		if(x==p->getX())
			x += 3;
		else
			x += getSpeed();
	}
	draw();
}

void Pea::draw()
{
	UserInterface::ConsoleOutput::getInstance()(x, y) << "-";
}

void Pea::update()
{
	if (Game::getInstance().getTime() % 1000 == 0) {
		Game& game = Game::getInstance();
		if (x == 100)
		{
			x = -1;
		}
		else if (x > 0 && x < 100)
		{
			move();

			for (auto z : game.zombies)
			{
				if (y == z->getY() && x == z->getX() - 1)
				{
					z->damage();
					if (z->getHealth() <= 0)
					{
						delete (z);
						game.zombies.remove(z);
						break;
					}
					x = -1;
					return;
				}
			}
		}
	}
}