#pragma once
#include "Zombie.h"
class BucketHead :
	 virtual public Zombie
{
public:
	BucketHead(SHORT, SHORT);
	void interaction();
	void set();
};

