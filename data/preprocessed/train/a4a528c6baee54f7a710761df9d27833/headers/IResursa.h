#pragma once
#include "CPoint.h"
class IResursa
{
public:
	virtual bool Verify(CPoint P) = 0;
	virtual bool RemoveTime() = 0;
	virtual ~IResursa() { ; }
};

