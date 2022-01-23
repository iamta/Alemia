#pragma once
#include "CPoint.h"
#include <iostream>
#include <string>
using namespace std;
class IEntity
{
public:	
	virtual void TakeDemage(int Dmg) = 0;
	virtual bool Shoot() = 0;
	virtual int DealDemage() = 0;
	virtual void Draw() = 0;
	virtual ~IEntity() { ; };
};

