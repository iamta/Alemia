#include "CherryBomb.h"

CherryBomb::~CherryBomb()
{
}

void CherryBomb::takeDamage(int)
{
	damage = 0;
}

int CherryBomb::getDamage()
{
	return damage;
}

int CherryBomb::getLine()
{
	return line;
}

string CherryBomb::getType()
{
	return type;
}

int CherryBomb::getPosition()
{
	return position;
}

int CherryBomb::returnHealth()
{
	return 10;
}

void CherryBomb::moveBack()
{
}

void CherryBomb::move()
{
}
