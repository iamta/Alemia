#include "OrdinaryZoombie.h"




OrdinaryZoombie::OrdinaryZoombie(int level)
{
	srand(time(NULL));
	this->y = (rand() % level) * 3 + 7;
	this->x = 59;
	
}

void OrdinaryZoombie::set_linie(int y)
{
	this->y = y;
}

void OrdinaryZoombie::move()
{	
	x = x - 1;
	
}

void OrdinaryZoombie::is_hit()
{
	this->health--;
}

int OrdinaryZoombie::getx()
{
	return this->x;
}

int OrdinaryZoombie::gety()
{
	return this->y;
}

int OrdinaryZoombie::gethealth()
{
	return this->health;
}

char OrdinaryZoombie::getsign()
{
	return this->sign;
}


OrdinaryZoombie::~OrdinaryZoombie()
{
}
