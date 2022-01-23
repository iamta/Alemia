#include "Zombie_PoleVaulting.h"



Zombie_PoleVaulting::Zombie_PoleVaulting()
{
	is_jumped = 0;
}

Zombie_PoleVaulting::Zombie_PoleVaulting(int health, COORD A, int damage, int rezistenta, int viteza, string name,int time):Zombie(health,A,damage,rezistenta,viteza,name,time)
{
	is_jumped = 0;
}


Zombie_PoleVaulting::~Zombie_PoleVaulting()
{
}
