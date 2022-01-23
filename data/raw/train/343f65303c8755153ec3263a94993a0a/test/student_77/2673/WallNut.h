#pragma once

#include "Entity.h"

class WallNut:public Entity
{
	int health;
	int line;
	string type;
	int position;

public:

	WallNut(int, int, string, int);
	~WallNut();

	void takeDamage(int);
	int getLine();
	string getType();
	int getPosition();
	int getDamage();

	int returnHealth();

	void moveBack();
	void move();


};

