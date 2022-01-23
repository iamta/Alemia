#pragma once


#include <string>
using namespace std;


class Entity
{
public:

	virtual int getLine() = 0;
	virtual string getType() = 0;
	virtual int getPosition() = 0;
	virtual void move() = 0;
	virtual int getDamage() = 0;

	virtual void takeDamage(int) = 0;
	virtual int returnHealth() = 0;
	virtual void moveBack() = 0;

};

