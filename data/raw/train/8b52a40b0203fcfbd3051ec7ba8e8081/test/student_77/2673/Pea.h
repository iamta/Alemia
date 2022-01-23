#pragma once

#include "Inter_plante.h"

class Pea:public Inter_plante
{
	int damage;
	string type;
	int position;
	int line;

public:
	Pea(int a,int b,int c,string tp) :damage(a),position(b),line(c),type(tp) {}
	~Pea();


	void takeDamage(int);
	int getDamage();
	int getLine();
	string getType();
	int getPosition();
	int returnHealth();


	void moveBack();
	void move();

};

