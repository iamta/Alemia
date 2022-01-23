#pragma once

#include "IDrawable.h"

class Plant:
	public IDrawable
{
public:

	enum PlantType
	{
		Peashooter, Sunflower
	};

protected:

	PlantType plantType;

	int x;
	int y;
	int cost;
	int health;
	int time;

public:
	
	PlantType getPlantType() { return plantType; }

	Plant(int _x,int _y,int _cost, int _health, int t) :x(_x),y(_y),cost(_cost), health(_health), time(t) {};
	~Plant() {};

	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	virtual Plant* clone() = 0;

	int getx() { return x; }
	int gety() { return y; }
	int getCost() { return cost; }
	int getHealth() { return health; }
	int getTime() { return time; }

};

