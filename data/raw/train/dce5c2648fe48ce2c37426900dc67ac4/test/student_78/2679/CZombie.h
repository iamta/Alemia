#pragma once
#include "IDrawable.h"

class CZombie :
	public IDrawable

{
protected:

	static int count;
	int health;
	int speed;
	int x, y;

public:

	CZombie(int h, int s, int a, int b) : health(h), speed(s), x(a), y(b) {};
	virtual ~CZombie() {};

	int getHealth() { return health; }
	int getSpeed() { return speed; }
	int getX() { return x; }
	int getY() { return y; }

	void damage() { health--; }

	void move();
	virtual void draw() = 0;
	void update();
};

