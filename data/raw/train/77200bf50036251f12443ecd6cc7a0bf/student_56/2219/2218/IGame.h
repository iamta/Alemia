#pragma once
#include "UserAction.h"

class IGame
{
public:
	virtual void Start() = 0;
	virtual bool Update(UserAction new_action) = 0;
	virtual void End() = 0;

};