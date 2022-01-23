#pragma once

#include "Entity.h"

class CherryBomb:public Entity
{
	int damage;
	string type;
	int position;
	int line;

public:
	CherryBomb(int a, int b, int c, string tp) :damage(a), position(b), line(c), type(tp) {}
	~CherryBomb();


	void takeDamage(int);
	int getDamage();
	int getLine();
	string getType();
	int getPosition();
	int returnHealth();


	void moveBack();
	void move();
};

