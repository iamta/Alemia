#include "Resurse.h"

int Resurse::total = 150;

Resurse::Resurse()
{
}

void Resurse::update()
{
	UserInterface::ConsoleOutput::getInstance()(3, 0) << "Resurse:      ";
	UserInterface::ConsoleOutput::getInstance()(3, 0) << "Resurse: " << total;
}

Resurse::~Resurse()
{
}
