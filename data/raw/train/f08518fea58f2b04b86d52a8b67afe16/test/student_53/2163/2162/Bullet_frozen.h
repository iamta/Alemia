#pragma once
#include "Bullet.h"
class Bullet_frozen:public Bullet
{
	int slow;
public:
	Bullet_frozen();
	Bullet_frozen(int slow, COORD pos, char c);
	int get_slow() { return slow; }
	virtual~Bullet_frozen();
};