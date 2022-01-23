#include "BucketHeadZoombie.h"




BucketHeadZoombie::BucketHeadZoombie(int level)
{
	srand(time(NULL));
	this->y = (rand() % level) * 3 + 7;
	this->x = 59;
}

void BucketHeadZoombie::set_linie(int y)
{
	this->y = y;
}

void BucketHeadZoombie::move()
{
	x = x - 1;
}

void BucketHeadZoombie::is_hit()
{
	this->health--;
}

int BucketHeadZoombie::getx()
{
	return this->x;
}

int BucketHeadZoombie::gety()
{
	return this->y;
}

int BucketHeadZoombie::gethealth()
{
	return this->health;
}

char BucketHeadZoombie::getsign()
{
	return this->sign;
}


BucketHeadZoombie::~BucketHeadZoombie()
{
}
