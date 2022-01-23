#pragma once
#include <stdlib.h>
#include <time.h>
#define BATTLEFIELD_BEGIN 59


class Zoombie
{
public:
	Zoombie();
	virtual void set_linie(int y) = 0;
	virtual void move()=0;
	virtual int getx() = 0;
	virtual int gety() = 0;
	virtual void is_hit()=0;
	virtual int gethealth() = 0;
	virtual char getsign() = 0;
	
	~Zoombie();
};

