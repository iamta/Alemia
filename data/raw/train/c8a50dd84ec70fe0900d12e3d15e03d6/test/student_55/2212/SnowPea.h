#pragma once
#include "ShootingPlant.h"
#include "FrozenPea.h"



class SnowPea:public ShootingPlant
{
private:
	static int spawnTime;
	static int shootTime;
	chrono::steady_clock::time_point lastShot;
public:
	SnowPea(int x, int y) :ShootingPlant(100, 75, x, y) {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(y, x);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color,11);
		cout << (char)226;
		SetConsoleTextAttribute(color, 7);
	}
	static int getSpawnTime() { return spawnTime; }
	bool testTime() {
		auto shotTime = steady_clock::now();
		if (duration_cast<milliseconds>(shotTime - lastShot).count() > shootTime)
		{
			lastShot = shotTime;
			return true;
		}
		return false;
	}
	Projectile* shoot() {
		return new FrozenPea(y, x + 1, 1);
	};
};

