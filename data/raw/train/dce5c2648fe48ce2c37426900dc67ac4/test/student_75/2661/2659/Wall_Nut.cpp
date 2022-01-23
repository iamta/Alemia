#include "Wall_Nut.h"



Wall_Nut::Wall_Nut()
{
	get_viata() = 15;
	get_necesar_resurse() = 200;
	get_Coord() = { 52, 0, PLANTA, WALL_NUT };
	set_Culoare("\u001b[0m");
	set_Desen("||");
}


Wall_Nut::~Wall_Nut()
{
}
