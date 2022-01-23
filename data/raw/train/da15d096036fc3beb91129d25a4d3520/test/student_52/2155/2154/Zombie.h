#pragma once
#include"ZombieFather.h"
class Zombie:public ZombieFather
{
private:
	int X1;
	int Y1;
	bool alive = 0;
	bool fresh = 0;
	
	
public:
	string lastPos;
	Zombie() :ZombieFather(100, 3) { lastPos = "/ "; };

	void setCor(int a, int b)
	{
		X1 = a;
		Y1 = b;
	}

	

	int getX1()
	{
		return X1;
	}

	int getY1()
	{
		return Y1;
	}

	void setAlive()
	{
		alive = 1;
	}
	void setFresh()
	{
		fresh = 1;
	}

	void getKilled()
	{
		alive = 0;
	}

	bool getAlive()
	{
		return alive;
	}
	bool getFresh()
	{
		return fresh;
	}

	void lowerY1()
	{
		Y1--;
	}

	
	~Zombie() {};
	
};

