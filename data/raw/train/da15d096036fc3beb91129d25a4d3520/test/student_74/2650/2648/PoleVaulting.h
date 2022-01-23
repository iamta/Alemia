#pragma once
#include "Zombie.h"
class PoleVaulting :
	virtual public Zombie
{
	bool jumped=false;
public:
	PoleVaulting(SHORT, SHORT);
	void interaction();
	void set();
};

