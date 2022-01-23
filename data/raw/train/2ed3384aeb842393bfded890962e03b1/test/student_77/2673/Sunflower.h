#pragma once

#include "Inter_plante.h"

class Sunflower:public Inter_plante
{
	int health;
	int line;
	string type;
	int position;

public:

	Sunflower(int,int,string,int);
	~Sunflower();

	void takeDamage(int);
	int getLine();
	string getType();
	int getPosition();
	int getDamage();

	int returnHealth();

	void moveBack();
	void move();

};

