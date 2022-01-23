#pragma once

#include "Inter_plante.h"

#include "Pea.h"

class Peashooter:public Inter_plante
{
	int health;
	int line;
	string type;
	int position;

public:

	Peashooter(int, int,string,int);
	~Peashooter();


	void takeDamage(int);
	int getLine();
	string getType();
	int getPosition();
	int getDamage();

	int returnHealth();

	void moveBack();
	void move();
};

