#pragma once

#include "Entity.h"

class BucketHeadZombie:public Entity
{
	int health;
	int damage;
	int line;
	string type;
	int position;


public:

	BucketHeadZombie(int, int, int, string, int);
	~BucketHeadZombie();


	void takeDamage(int);
	int getLine();
	string getType();
	int getPosition();
	int getDamage();

	int returnHealth();

	void moveBack();
	void move();
};

