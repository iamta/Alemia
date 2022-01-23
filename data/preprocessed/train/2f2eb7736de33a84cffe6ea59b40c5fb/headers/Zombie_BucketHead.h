#pragma once
#include "Zombie.h"
class Zombie_BucketHead:virtual public Zombie
{

public:
	Zombie_BucketHead();
	Zombie_BucketHead(int health, COORD A, int damage, int rezistenta, int viteza, string name,int time);
	virtual~Zombie_BucketHead();
};

