#pragma once
#include "PoleVaulting.h"
#include "BucketHead.h"
class Super :
	virtual public PoleVaulting, virtual public BucketHead
{
	bool jumped = false;
public:
	Super(SHORT, SHORT);
	void interaction();
	void set();
};

