#include "Peashooter.h"

Peashooter::Peashooter(int hp, int ln, string tp,int pos): health(hp),line(ln),type(tp),position(pos)
{
}

Peashooter::~Peashooter()
{
}

void Peashooter::takeDamage(int a)
{
	health -= a;
}

int Peashooter::getLine()
{
	return line;
}

string Peashooter::getType()
{
	return type;
}

int Peashooter::getPosition()
{
	return position;
}

int Peashooter::getDamage()
{
	return health;
}

int Peashooter::returnHealth()
{
	return health;
}

void Peashooter::moveBack()
{
}

void Peashooter::move()
{
}

