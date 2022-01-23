#pragma once
#include "Entity.h"
#include "Resurse.h"
class Plant: public Entity
{
protected:
	char c;
	int cost;
public:
	Plant();
	Plant(char c_1, int health, COORD A,int cost_1);
	virtual void print();
	void sterge();
	char get_char() { return c; }

	int get_cost() { return cost; }
	virtual~Plant();
};