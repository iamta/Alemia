#pragma once
#include "Bullet.h"
class Bullet_normal:public Bullet
{
	int damage;
public:
	Bullet_normal();
	Bullet_normal(int damage, COORD pos, char c);
	int get_damage() { return damage; }
	virtual~Bullet_normal();
};