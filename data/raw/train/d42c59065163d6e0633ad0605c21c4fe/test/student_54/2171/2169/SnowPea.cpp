#include "SnowPea.h"



SnowPea::SnowPea()
{
}

SnowPea::SnowPea(int x, int y)
{
	this->x = x;
	this->y = y;
}



int SnowPea::get_baseCoord()
{
	return this->baseCoord;
}

int SnowPea::get_x()
{
	return this->x;
}

int SnowPea::get_y()
{
	return this->y;
}

int SnowPea::get_cost()
{
	return this->cost;
}

string SnowPea::get_item()
{
	return this->item;
}


void SnowPea::injury()
{
	health--;
}

int SnowPea::get_health()
{
	return this->health;
}


SnowPea::~SnowPea()
{
}
