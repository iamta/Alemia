#pragma once
#include "Bulet.h"

class Frozen :
	public Bulet
{
public:
	Frozen(SHORT, SHORT, int);
	void set();
	void slow();
};

