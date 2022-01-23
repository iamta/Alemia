#include "SunFlower.h"



SunFlower::SunFlower()
{
}

SunFlower::SunFlower(int x, int y)
{
	this->x = x;
	this->y = y;
}



int SunFlower::get_baseCoord()
{
	return this->baseCoord;
}

int SunFlower::get_x()
{
	return this->x;
}

int SunFlower::get_y()
{
	return this->y;
}

int SunFlower::get_cost()
{
	return this->cost;
}

string SunFlower::get_item()
{
	return this->item;
}

void SunFlower::injury()
{
	health--;
}

int SunFlower::get_health()
{
	return this->health;
}



SunFlower::~SunFlower()
{
}
