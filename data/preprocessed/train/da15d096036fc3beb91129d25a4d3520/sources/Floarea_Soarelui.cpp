#define _CRT_SECURE_NO_WARNINGS
#include "Floarea_Soarelui.h"
#include <fstream>
#include <io.h>
#include <fcntl.h>



Floarea_Soarelui::Floarea_Soarelui()
{
	
	get_viata() = 5;
	get_necesar_resurse() = 100;
	get_Coord() = { 4, 0, PLANTA, FLOAREA_SOARELUI };
	set_Culoare("\u001b[33m");
	set_Desen("&");
}

Floarea_Soarelui::~Floarea_Soarelui()
{
}
