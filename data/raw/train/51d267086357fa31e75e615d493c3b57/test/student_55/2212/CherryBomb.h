#pragma once
#include "Plant.h"

class CherryBomb:public Plant
{
private:
	static int spawnTime;
public:
	CherryBomb(int x, int y) :Plant(50, 50, x, y) {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(y, x);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 4);
		cout << (char)229;
		SetConsoleTextAttribute(color, 7);
	}
	static int getSpawnTime() { return spawnTime; }
	~CherryBomb() {};
};

