#pragma once

#include <Windows.h>

#include "ConsoleOutput.h"

class IDrawable
{
public:

	virtual int getX() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
};
