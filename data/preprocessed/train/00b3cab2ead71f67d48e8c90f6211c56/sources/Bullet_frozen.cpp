#include "Bullet_frozen.h"



Bullet_frozen::Bullet_frozen()
{
	slow = 10;
}

Bullet_frozen::Bullet_frozen(int slow, COORD pos, char c):Bullet(pos.X,pos.Y,c)
{
	this->slow = slow;
}


Bullet_frozen::~Bullet_frozen()
{
}
