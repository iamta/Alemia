#include "Peashooter.h"
#include "ConsoleOutput.h"
#include "Joc.h"
#include "Pea.h"

Peashooter::~Peashooter()
{
	UserInterface::ConsoleOutput::getInstance(x, y) << "   ";
	UserInterface::ConsoleOutput::getInstance(x, y + 1) << " ";
}

void Peashooter::draw()
{
	UserInterface::ConsoleOutput::getInstance(x, y) << "C>=";
	UserInterface::ConsoleOutput::getInstance(x, y+1) << "/";
}

void Peashooter::update()
{
	if (Game::getInstance().getTime() % 24000 == 0) {

		Game::getInstance().projectiles.push_back(new Pea(x + 3, y));

	}
}
