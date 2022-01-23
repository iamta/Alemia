#pragma once
#include "Zombie.h"
class Zombie_PoleVaulting:virtual public Zombie
{
	int is_jumped;
public:
	Zombie_PoleVaulting();
	Zombie_PoleVaulting(int health, COORD A, int damage, int rezistenta, int viteza, string name,int time);
	void set_is_jumped(int i) { is_jumped = i; }
	int get_is_jumped() { return is_jumped; }
	virtual~Zombie_PoleVaulting();
};

