#pragma once
#include <iostream>
#include "PeaShooter.h"
#include "SnowPea.h"
#include "WallNut.h"
#include "SunFlower.h"
#include "CherryBomb.h"

using namespace std;
class Map
{
public:
	static Map& getInstance();

	void displayFirstLevel();
	void displaySecondLevel();
	void displayThirdLevel();
	void displayShop();
private:
	static Map* instance;

	Map() {};
	Map(const Map&) {};
	~Map() {};
};

