#include "Proiectil.h"



Proiectil::Proiectil(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Proiectil::move()
{
	x = x + 1;
}

int Proiectil::getx()
{
	return this->x;;
}

int Proiectil::gety()
{
	return this->y;
}



Proiectil::~Proiectil()
{
}
