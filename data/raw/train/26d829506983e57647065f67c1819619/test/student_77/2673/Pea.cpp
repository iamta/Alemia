#include "Pea.h"

Pea::~Pea()
{
}

void Pea::takeDamage(int )
{
	damage = 0;
}

int Pea::getDamage()
{
	return damage;
}

int Pea::getLine()
{
	return line;
}

string Pea::getType()
{
	return type;
}

int Pea::getPosition()
{
	return position;
}

int Pea::returnHealth()
{
	return 10;
}

void Pea::moveBack()
{
}

void Pea::move()
{
	position++;
}
