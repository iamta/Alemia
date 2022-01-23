#pragma once
#include "Resurse.h"
class Sun: public  Resurse
{
protected:
	COORD old;
	int selected;
public:
	Sun();
	Sun(int x, int y);
	COORD get_old_coord() { return old; }
	int get_selcted() { return selected; }
	void set_selected(int x) { selected = x; }
	virtual~Sun();
};

