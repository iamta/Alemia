#pragma once
#include<iostream>
using namespace std;
class Pea
{
private:
	int X1;
	int X2;
	int Y1;
	int Y2;
	int life = 100;
	int projPos = 0;
	bool shot = 0;
	

public:
	bool dead = 0;
	Pea()
	{
		X1 = 0;
		Y1 = 0;
		X2 = 0;
		Y2 = 0;
		life = 100;
		shot = 0;
	}

	void setPos(int x1, int x2, int y1, int y2)
	{
		X1 = x1;
		X2 = x2;
		Y1 = y1;
		Y2 = y2;
	}

	int getHP()
	{
		return life;
	}

	void print()
	{
		std::cout << X1 << " " << X2 << " - " << Y1 << " " << Y2 << "\n";
	}

	int getX1()
	{
		return X1;
	}

	void lowerHP()
	{
		life -= 50;
	}

	int getX2()
	{
		return X2;
	}
	int getY2()
	{
		return Y2;
	}
	void setShot()
	{
		shot = 1;
	}
	int getProjPos()
	{
		return projPos;
	}

	void setProjPos(int i)
	{
		projPos = i;
	}
	bool getShot()
	{
		return shot;
	}
	void resetShot()
	{
		shot = 0;
	}
};

