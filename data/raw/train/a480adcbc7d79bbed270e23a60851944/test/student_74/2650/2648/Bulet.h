#pragma once
#include "LifeForm.h"
class Bulet :
	public LifeForm
{
public:
	Bulet(SHORT, SHORT, int dmg = 20);
	virtual void set() = 0;
	void draw();
	void move();
	void delete_tail();
	void interaction();
};

