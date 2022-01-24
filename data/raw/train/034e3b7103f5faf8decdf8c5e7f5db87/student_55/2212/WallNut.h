#pragma once
#include "Plant.h"

class WallNut:public Plant
{
private:
	static int SpawnTime;
public:
	WallNut( int x, int y) :Plant(200, 50, x, y) {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(y, x);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 12);
		cout << (char)225;
		SetConsoleTextAttribute(color, 7);
	}
	static int getSpawnTime() { return SpawnTime; }
	~WallNut() {
		
	}
};

