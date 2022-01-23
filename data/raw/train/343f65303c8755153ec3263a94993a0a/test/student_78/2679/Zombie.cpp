#include "Zombie.h"

Zombie::~Zombie()
{
	UserInterface::ConsoleOutput::getInstance(x, y) << "   ";
}

void Zombie::draw()
{
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	conOut(x, y) << "|~|";
}

