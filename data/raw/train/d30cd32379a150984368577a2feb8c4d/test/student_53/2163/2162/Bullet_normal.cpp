#include "Bullet_normal.h"



Bullet_normal::Bullet_normal()
{
	damage = 10;
}

Bullet_normal::Bullet_normal(int damage, COORD pos, char c):Bullet(pos.X,pos.Y,c)
{
	this->damage = damage;
}


Bullet_normal::~Bullet_normal()
{
}
