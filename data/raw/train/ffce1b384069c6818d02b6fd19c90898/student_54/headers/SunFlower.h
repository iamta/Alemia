#pragma once
#include "Plant.h"
class SunFlower:public Plant
{
private:
	int baseCoord = 7;
	int x;
	int y;
	int cost = 50;
	int health = 5;
	string item = "SF";
public:
	SunFlower();
	SunFlower(int x, int y);
	int get_baseCoord();
	int get_x();
	int get_y();
	int get_cost();
	string get_item();
	bool attack() { return false; }
	void injury();
	int get_health();
	~SunFlower();
};

