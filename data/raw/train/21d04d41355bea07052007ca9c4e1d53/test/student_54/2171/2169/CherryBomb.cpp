#include "CherryBomb.h"



CherryBomb::CherryBomb()
{
}


CherryBomb::CherryBomb(int x, int y)
{
	this->x = x;
	this->y = y;
}



int CherryBomb::get_baseCoord()
{
	return this->baseCoord;
}

int CherryBomb::get_x()
{
	return this->x;
}

int CherryBomb::get_y()
{
	return this->y;
}

int CherryBomb::get_cost()
{
	return this->cost;
}

string CherryBomb::get_item()
{
	return this->item;
}

bool CherryBomb::attack()
{
	return false;
}


CherryBomb::~CherryBomb()
{
}
