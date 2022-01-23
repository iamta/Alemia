#include "Super_Zombie.h"

using namespace Oaspete;

Super_Zombie::Super_Zombie()
{
	get_viata() = 30;
	set_Culoare("\u001b[31m");
	set_Desen("|=(+_+)=| ");
	set_Type(Z);
	get_Coord() = { 0, 225, ZOMBIE, NO };
	Jump = true;
}


Super_Zombie::~Super_Zombie()
{
}
