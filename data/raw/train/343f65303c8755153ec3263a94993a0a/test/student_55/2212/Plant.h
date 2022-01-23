#pragma once
#include <iostream>
#include "IDrawable.h"
#include "Projectile.h"
using namespace std;

class Plant :public IDrawable
{
protected:
	int health;
	int price;
public:
	Plant(int health, int price, int X, int Y) :health(health)
	{
		this->price = price;
		x = X;
		y = Y;
	};
	int getPrice() { return price; }
	int getHealth() { return health; }
	void getDamage(int amount) { health -= amount; }
	virtual ~Plant() {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(y, x) << " ";
	}
};

