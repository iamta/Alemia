#pragma once
#include "Plant.h"
#include "Frozen.h"
class FrozenPeaShooter :
	public Plant
{
	std::vector<Frozen*> bulets;
public:
	FrozenPeaShooter(SHORT, SHORT);
	void interaction();
	void set();
};

