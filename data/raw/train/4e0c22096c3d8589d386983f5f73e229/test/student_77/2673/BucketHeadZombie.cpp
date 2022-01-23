#include "BucketHeadZombie.h"

BucketHeadZombie::BucketHeadZombie(int hp, int dmg, int ln, string tp, int pos) :health(hp), damage(dmg), line(ln), type(tp), position(pos)
{
}

BucketHeadZombie::~BucketHeadZombie()
{
}

void BucketHeadZombie::takeDamage(int a)
{
	health -= a;
}

int BucketHeadZombie::getLine()
{
	return line;
}

string BucketHeadZombie::getType()
{
	return type;
}

int BucketHeadZombie::getPosition()
{
	return position;
}

int BucketHeadZombie::getDamage()
{
	return damage;
}

int BucketHeadZombie::returnHealth()
{
	return health;
}

void BucketHeadZombie::moveBack()
{
	position++;
}

void BucketHeadZombie::move()
{
	position--;
}
