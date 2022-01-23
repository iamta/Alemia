#include "Sunflower.h"

Sunflower::Sunflower(int hp, int ln, string tp,int pos) : health(hp), line(ln), type(tp),position(pos)
{
}

Sunflower::~Sunflower()
{
}

void Sunflower::takeDamage(int a)
{
	health -= a;
}

int Sunflower::getLine()
{
	return line;
}

string Sunflower::getType()
{
	return type;
}

int Sunflower::getPosition()
{
	return position;
}

int Sunflower::getDamage()
{
	return health;
}

int Sunflower::returnHealth()
{
	return health;
}

void Sunflower::moveBack()
{
}

void Sunflower::move()
{
}


