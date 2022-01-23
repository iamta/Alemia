#pragma once
class Pea
{
protected:

	int x, y;
	int speed = 1;

public:

	Pea(int a, int b) : x(a), y(b) {};
	~Pea();

	int getx() { return x; }
	int gety() { return y; }
	int getSpeed() { return speed; }

	void move();
	void draw();
	void update();

};

