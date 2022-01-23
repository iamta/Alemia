#pragma once
#include "ConsoleOutput.h"
class Field
{
public:
	Field();
	virtual ~Field();
	virtual const void print_field() const = 0;
};

