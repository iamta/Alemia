#include "Sun.h"

Sun* Sun::ptr = nullptr;

int Sun::numar_de_sori = 8;
int Sun::numarul_actual = 0;
int Resurse::valoare = 50;

Sun::Sun()
{
	up = false;
	set = false;
}

Sun* Sun::getInstance()
{
	if (numarul_actual <= numar_de_sori)
	{
		ptr = new Sun;
		numarul_actual++;
	}
	return ptr;
}

void Sun::Draw(coordonate &where)
{
	UserInterface::ConsoleOutput::getInstance()(where.x, where.y) << "\u001b[33m*\u001b[37m";
}





Sun::~Sun()
{
}
