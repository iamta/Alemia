#pragma once
#include "Plant.h"
class Sunflower:
	public Plant
{
	bool rate = false;
public:
	Sunflower(SHORT, SHORT);
	void interaction();
	void set();
};

