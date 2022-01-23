#include "Zombie_SuperZombie.h"



Zombie_SuperZombie::Zombie_SuperZombie()
{
}

Zombie_SuperZombie::Zombie_SuperZombie(int health, COORD A, int damage, int rezistenta, int viteza, string name,int time):Zombie_BucketHead(health, A, damage, rezistenta, viteza, name,time),Zombie_PoleVaulting(health, A, damage, rezistenta, viteza, name,time)
{
}


Zombie_SuperZombie::~Zombie_SuperZombie()
{
}
