#pragma once

#include "CZombie.h"


class Zombie :
	public CZombie
{
public:
	Zombie(int x,int y) :CZombie(3, 4,x, y) {};
	~Zombie();

	void draw() override;
};

