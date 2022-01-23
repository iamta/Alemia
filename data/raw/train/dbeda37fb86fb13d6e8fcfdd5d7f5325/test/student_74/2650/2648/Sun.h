#pragma once
#include "Box.h"
class Sun :
	public Box
{
	static int ammount;
	static int rate;
public:
	Sun(SHORT, SHORT);
	static void set_rate(int rate1) { rate = rate1; }
	static int get_rate() { return rate; }
	static void increase_ammount() { ammount += 25; }
	static int get_ammount() { return ammount; }
	static bool pay(int cost);
	void set();
	void draw();
	void clear();
};

