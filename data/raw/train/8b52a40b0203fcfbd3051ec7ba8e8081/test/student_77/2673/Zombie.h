#pragma once

#include "Inter_plante.h"

class Zombie:public Inter_plante
{
	int health;
	int damage;
	int line;
	string type;
	int position;


public:

	Zombie(int, int,int, string ,int);
	~Zombie();


	void takeDamage(int);
	int getLine();
	string getType();
	int getPosition();
	int getDamage();

	int returnHealth();

	void moveBack();
	void move();

};

