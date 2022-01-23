#pragma once
#include "Plant.h"
#include "NormalB.h"
class PeaShooter :
	public Plant
{
	std::vector<NormalB*> bulets;
public:
	PeaShooter(SHORT, SHORT);
	void interaction();
	void set();
};

