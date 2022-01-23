#include "Cheery.h"



Cheery::Cheery()
{
	get_viata() = -1;
	get_necesar_resurse() = 150;
	get_Coord() = { 40, 0, PLANTA, CHEERY };
	set_Culoare("\u001b[31m");
	set_Desen("*");
}


Cheery::~Cheery()
{
}
