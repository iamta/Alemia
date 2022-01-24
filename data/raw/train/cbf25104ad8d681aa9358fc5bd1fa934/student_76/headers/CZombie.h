#pragma once
#include "CAEntity.h"
class CZombie:public CAEntity
{
public:
	void Draw();
	bool Shoot() { return false; }
	CZombie(CPoint P);
	~CZombie();
};

