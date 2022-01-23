#include "Sun.h"

Sun::Sun()
{
	x = 0;
	y = 0;
}

Sun::~Sun()
{
}

void Sun::SetX(int x)
{
	this->x = x;
}

void Sun::SetY(int y)
{
	this->y = y;
}

int Sun::GetX()
{
	return x;
}

int Sun::GetY()
{
	return y;
}

const char * Sun::GetForma()
{
	return forma.c_str();
}

int Sun::GetVal()
{
	return val;
}
