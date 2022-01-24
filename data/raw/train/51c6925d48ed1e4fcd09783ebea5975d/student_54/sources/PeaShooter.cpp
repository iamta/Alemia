#include "PeaShooter.h"



PeaShooter::PeaShooter()
{
}

PeaShooter::PeaShooter(int x,int y)
{
	this->x = x;
	this->y = y;
}


int PeaShooter::get_baseCoord()
{
	return this->baseCoord;
}

int PeaShooter::get_x()
{
	return this->x;
}

int PeaShooter::get_y()
{
	return this->y;
}

int PeaShooter::get_cost()
{
	return this->cost;
}

string PeaShooter::get_item()
{
	return this->item;
}



void PeaShooter::injury()
{
	health--;
}

int PeaShooter::get_health()
{
	return this->health;
}


PeaShooter::~PeaShooter()
{
}
