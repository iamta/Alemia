#pragma once
#include "LifeForm.h"
class Plant :
	public LifeForm
{
	int cost;
public:
	Plant(SHORT, SHORT);
	void draw();
	int get_cost() { return cost; }
	void set_cost(int cost) { this->cost = cost; }
	COORD snap_to_grid();
	virtual void interaction() = 0;
	virtual void set() = 0;
};

