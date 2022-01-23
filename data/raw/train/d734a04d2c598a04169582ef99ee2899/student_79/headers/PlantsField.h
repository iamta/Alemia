#pragma once
#include "Field.h"
class PlantsField : public Field
{
private:
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	PlantsField();
	~PlantsField();
	const void print_field() const;
};

