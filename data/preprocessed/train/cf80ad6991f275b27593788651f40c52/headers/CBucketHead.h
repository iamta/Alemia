#pragma once
#include "CAEntity.h"
class CBucketHead:public CAEntity
{
public:
	void Draw();
	bool Shoot() { return false; }
	CBucketHead(CPoint P);
	~CBucketHead();
};

