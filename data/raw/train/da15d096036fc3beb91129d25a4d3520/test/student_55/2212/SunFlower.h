#pragma once
#include "Plant.h"
#include "Sun.h"

class SunFlower:public Plant
{
private:
	static int spawnTime;
public:
	SunFlower(int x, int y) :Plant(50, 50, x, y) {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(y, x);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 14);
		cout << (char)234;
		SetConsoleTextAttribute(color, 7);
		Sun::reduceSunSpawnTime();
	}
	static int getSpawnTime() { return spawnTime; }
	~SunFlower() {
		Sun::restoreSunSpawnTime();
	}
};

