#pragma once
#include "Plant.h"

class SnowPea:public Plant
{
private:
	int baseCoord = 19;
	int x;
	int y;
	int cost = 100;
	int health = 5;
	string item = "SP";

public:

	SnowPea();
	SnowPea(int x, int y);
	int get_baseCoord();
	int get_x();
	int get_y();
	int get_cost();
	string get_item();
	bool attack() { return true; }
	void injury();
	int get_health();

	~SnowPea();
};

