#pragma once
#include "Plant.h"
#include "ConsoleOutput.h"
#include <windows.h>
#include "Projectile.h"
#include <chrono>
#include <time.h>

class ShootingPlant:public Plant
{
public:
	ShootingPlant(int health, int price, int X, int Y) :Plant(health, price, X, Y) {};

	virtual Projectile* shoot() = 0;
	virtual bool testTime() = 0;
	virtual ~ShootingPlant() {};
};

