#pragma once
class Chronometer
{
private:
	Chronometer();
	~Chronometer();
	static Chronometer*instance;

public:
	static Chronometer &getInstance();
	static void destroyInstance();
	bool timer_sun(int existed_sunflowers);
	bool timer_plant();
	bool timer_wave();
	bool move();
	bool shoot();
	bool timer_zoombie();
	bool refresh();
	bool timer_bucketheadzoombie();
	
};

