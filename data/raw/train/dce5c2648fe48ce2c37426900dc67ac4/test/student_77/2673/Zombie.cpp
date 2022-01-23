#include "Zombie.h"


Zombie::Zombie(int hp, int dmg , int ln, string tp, int pos):health(hp),damage(dmg),line(ln),type(tp),position(pos)
{
}

Zombie::~Zombie()
{
}

void Zombie::takeDamage(int a)
{ 
	health -= a;
}

int Zombie::getLine()
{
	return line;
}

string Zombie::getType()
{
	return type;
}

int Zombie::getPosition()
{
	return position;
}

int Zombie::getDamage()
{
	return damage;
}

int Zombie::returnHealth()
{
	return health;
}

void Zombie::moveBack()
{
	position++;
}

void Zombie::move()
{
	position--;
}
