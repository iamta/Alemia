#include "Pole_Vaulting_Zombie.h"

using namespace Oaspete;

Pole_Vaulting_Zombie::Pole_Vaulting_Zombie()
{
	get_viata() = 20;
	set_Culoare("\u001b[33m");
	set_Desen("\\=(*-*)=/ ");
	get_Coord() = { 0, 225, ZOMBIE, NO };
	set_Type(P_V);
	Jump = true;
}


Pole_Vaulting_Zombie::~Pole_Vaulting_Zombie()
{
}
