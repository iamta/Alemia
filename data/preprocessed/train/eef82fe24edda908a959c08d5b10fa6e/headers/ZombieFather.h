#pragma once
#include<iostream>
using namespace std;
class ZombieFather
{
private:
	int health;
	int speed;


public:

	 ZombieFather() { health = 0; speed = 0; };
	ZombieFather(int x,int y) 
	{
		health = x;
		speed = y;
	}

	~ZombieFather() {};

	virtual void setValues(int x,int y)
	{
		health = x;
		speed = y;
	}

	virtual void print()
	{
		cout << health << " " << speed;
	}

	virtual void lowerHP()
	{
		health -= 50;
	}

	virtual int getHP()
	{
		return health;
	}
	

	
};

