#pragma once
#include "Plant.h"
class WallNut:public Plant
{
private:
	int baseCoord = 16;
	int x;
	int y;
	int cost = 100;
	int health = 20;
	string item = "WN";

public:
	WallNut();
	WallNut(int x, int y);
	int get_baseCoord();
	int get_x();
	int get_y();
	int get_cost();
	string get_item();
	bool attack() { return false; }
	void injury();
	int get_health();
	~WallNut();
};

