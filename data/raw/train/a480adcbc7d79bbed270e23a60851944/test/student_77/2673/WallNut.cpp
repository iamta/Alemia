#include "WallNut.h"

WallNut::WallNut(int hp, int ln, string tp, int pos) : health(hp), line(ln), type(tp), position(pos)
{
}

WallNut::~WallNut()
{
}

void WallNut::takeDamage(int a)
{
	health -= a;
}

int WallNut::getLine()
{
	return line;
}

string WallNut::getType()
{
	return type;
}

int WallNut::getPosition()
{
	return position;
}

int WallNut::getDamage()
{
	return health;
}

int WallNut::returnHealth()
{
	return health;
}

void WallNut::moveBack()
{
}

void WallNut::move()
{
}

