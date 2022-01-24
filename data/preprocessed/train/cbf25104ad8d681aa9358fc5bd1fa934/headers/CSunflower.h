#pragma once
#include "CAEntity.h"
class CSunflower:public CAEntity
{
public:
	void Draw();
	bool Shoot() { return false; }
	CSunflower(CPoint P);
	~CSunflower();
};

