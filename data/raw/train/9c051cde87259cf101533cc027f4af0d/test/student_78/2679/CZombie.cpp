#include <iostream>
#include<Windows.h>

#include "ConsoleOutput.h"
#include "CZombie.h"
#include "Joc.h"

void CZombie::move()
{
	Game& game = Game::getInstance();
	UserInterface::ConsoleOutput::getInstance()(x, y) << "   ";

	for (auto z : game.zombies)
	{
		if (z->getHealth() <= 0)
		{
			delete (z);
			game.zombies.remove(z);
			break;
		}
	}

	x -= getSpeed();
	draw();
}


void CZombie::update()
{
	if (Game::getInstance().getTime() % 50000 == 0) {

		this->move();
		if (x <= 5)
			Game::getInstance().setOver(true);
	}
}