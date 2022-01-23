#include "Mazare.h"



Mazare::Mazare()
{
	get_viata() = 7;
	get_necesar_resurse() = 125;
	get_Coord() = { 16, 0, PLANTA, BEAN };
	set_Culoare("\u001b[32m");
	set_Desen("%");
	proiectil.set_Desen("\u001b[32m  ->\u001b[37m");
	proiectil.set_tip(B);
}


Mazare::~Mazare()
{
}
