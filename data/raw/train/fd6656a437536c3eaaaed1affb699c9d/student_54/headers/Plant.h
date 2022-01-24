#pragma once
#include<string>

using namespace std;

class Plant
{
public:
	
	virtual int get_baseCoord()=0;
	virtual int get_x()=0;
	virtual int get_y()=0;
	virtual int get_cost() = 0;
	virtual string get_item() = 0;
	virtual bool attack()=0;
	virtual void injury() = 0;
	virtual int get_health() = 0;

	
};

