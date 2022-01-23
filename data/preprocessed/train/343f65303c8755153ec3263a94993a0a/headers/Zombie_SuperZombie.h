#pragma once
#include "Zombie_BucketHead.h"
#include "Zombie_PoleVaulting.h"
class Zombie_SuperZombie: public Zombie_BucketHead, public Zombie_PoleVaulting
{
public:
	Zombie_SuperZombie();
	Zombie_SuperZombie(int health, COORD A, int damage, int rezistenta, int viteza, string name,int time);
	virtual~Zombie_SuperZombie();
};