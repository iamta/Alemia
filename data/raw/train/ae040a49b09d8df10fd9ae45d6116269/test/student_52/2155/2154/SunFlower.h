#pragma once
#include<iostream>
using namespace std;
class SunFlower
{
private:
	int X1;
	int X2;
	int Y1;
	int Y2;
	int life = 50;


public:

	SunFlower() 
	{
		X1 = 0;
		Y1 = 0;
		X2 = 0;
		Y2 = 0;
		life = 50;
	};

	void setPos(int x1, int x2,int y1,int y2)
	{
		X1 = x1;
		X2 = x2;
		Y1 = y1;
		Y2 = y2;
	}

	void print()
	{
		std::cout << X1 << " " << X2 << " - " << Y1 << " " << Y2 << "\n";
	}

	int getX1()
	{
		return X1;
	}

	int getX2()
	{
		return X2;
	}

	void lowerHP()
	{
		life -= 25;
	}

	int getHP()
	{
		return life;
	}


};

