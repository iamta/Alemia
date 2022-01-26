#include "Proiectil.h"

Proiectil::Proiectil()
{
}

Proiectil::~Proiectil()
{
}

void Proiectil::SetForma(char forma)
{
	this->forma = forma;
}

void Proiectil::SetDemage(int demage)
{
	this->demage = demage;
}

void Proiectil::SetX(int x)
{
	this->x = x;
}

void Proiectil::SetY(int y)
{
	this->y = y;
}

char  Proiectil::GetForma()
{
	return forma;
}

int Proiectil::GetDemage()
{
	return demage;
}

int Proiectil::GetX()
{
	return x;
}

int Proiectil::GetY()
{
	return y;
}
