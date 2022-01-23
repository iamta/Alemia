#pragma once
#include "Box.h"
class LifeForm :
	public Box
{
	int hp;
	int damage;
public:
	int get_hp() { return hp; }
	int get_damage() { return damage; }
	void set_hp(int hp) { this->hp = hp; }
	void set_damage(int damage) { this->damage = damage; }
	bool died();
	virtual void interaction() = 0;
	virtual void set() = 0;
	virtual void draw() = 0;
	void clear();
};

