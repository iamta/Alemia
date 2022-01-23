#pragma once
#include "CZombie.h"

class BucketHeadZombie :
	public CZombie
{
public:

	BucketHeadZombie(int x, int y) : CZombie(6, 4, x, y) {};
	~BucketHeadZombie();

	void draw() override;
};

