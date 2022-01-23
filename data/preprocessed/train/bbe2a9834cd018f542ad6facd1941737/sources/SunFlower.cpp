#include "SunFlower.h"
#include "Joc.h"

SunFlower::~SunFlower()
{
	UserInterface::ConsoleOutput::getInstance(x, y) << "   ";
	UserInterface::ConsoleOutput::getInstance(x, y + 1) << " ";
}

void SunFlower::draw()
{
	UserInterface::ConsoleOutput::getInstance(x, y) << "(o)";
	UserInterface::ConsoleOutput::getInstance(x+1, y + 1) << "|";
}

void SunFlower::update()
{
	if (Game::getInstance().getTime() % 80000 == 0) {

		Game::getInstance().suns.push_back(Sun::SunFactory());
	}
}
