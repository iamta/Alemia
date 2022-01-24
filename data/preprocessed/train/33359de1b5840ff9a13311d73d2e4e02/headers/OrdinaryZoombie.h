#pragma once
#include "Zoombie.h"

class OrdinaryZoombie:public Zoombie
{
private:
	int x;
	int y;
	int health=5;
	int speed=1;
	char sign = 'Z';

public:

	OrdinaryZoombie(int level);
	virtual void set_linie(int y);
	virtual void move();
	virtual void is_hit();
	virtual int getx();
	virtual int gety();
	virtual int gethealth();
	virtual char getsign();
	~OrdinaryZoombie();
};

