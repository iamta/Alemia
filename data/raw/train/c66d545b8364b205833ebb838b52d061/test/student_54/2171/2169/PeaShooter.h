#pragma once
#include "Plant.h"

class PeaShooter:public Plant
{
private:
	int baseCoord = 10;
	int x;
	int y;
	int cost = 75;
	int health = 5;
	string item = "PS";
public:
	PeaShooter();
	PeaShooter(int x,int y);
	int get_baseCoord();
	int get_x();
	int get_y();
	int get_cost();
	string get_item();
	bool attack() { return true; }
	void injury();
	int get_health();
	~PeaShooter();
};

