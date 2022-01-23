#include "WallNut.h"



WallNut::WallNut()
{
}

WallNut::WallNut(int x, int y)
{
	this->x = x;
	this->y = y;
}



int WallNut::get_baseCoord()
{
	return this->baseCoord;
}

int WallNut::get_x()
{
	return this->x;
}

int WallNut::get_y()
{
	return this->y;
}

int WallNut::get_cost()
{
	return this->cost;
}

string WallNut::get_item()
{
	return this->item;
}

void WallNut::injury()
{
	health--;
}

int WallNut::get_health()
{
	return this->health;
}


WallNut::~WallNut()
{
}
