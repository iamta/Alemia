#pragma once
#include "Zoombie.h"

class BucketHeadZoombie:public Zoombie
{
private:
	int x;
	int y;
	int health = 8;
	int speed = 1;
	char sign = 'B';
	

public:
	BucketHeadZoombie(int level);
	virtual void set_linie(int y);
	virtual void move();
	virtual void is_hit();
	virtual int getx();
	virtual int gety();
	virtual int gethealth();
	virtual char getsign();
	~BucketHeadZoombie();
};

