#pragma once
#include "Plant.h"
class CherryBomb:public Plant
{
private:
	int baseCoord = 13;
	int x;
	int y;
	int cost = 150;
	string item = "CB";

public:
	CherryBomb();
	CherryBomb(int x, int y);
	int get_baseCoord();
	int get_x();
	int get_y();
	int get_cost();
	string get_item();
	bool attack();
	void injury() {};
	int get_health() { return 0; }
	~CherryBomb();
};

