#pragma once
#include "LifeForm.h"
class Zombie :
	public LifeForm
{
	int speed;
protected:
	int base_speed;
public:
	Zombie(SHORT, SHORT);
	void draw();
	int get_base_speed() { return base_speed; }
	void set_base_speed(int ns) { base_speed = ns; }
	int get_speed() { return speed; }
	void set_speed(int ns) { speed = ns; }
	virtual void interaction() = 0;
	virtual void set() = 0;
	void move();
	void delete_trail();
};

