#include "Chronometer.h"
#include <time.h>
#include <chrono>
using namespace std::chrono;

Chronometer*Chronometer::instance = 0;

Chronometer::Chronometer()
{
}

Chronometer &Chronometer::getInstance()
{
	if (!Chronometer::instance)
	{
		Chronometer::instance = new Chronometer();
	}

	return * Chronometer::instance;
}


bool Chronometer::timer_sun(int existed_sunflowers)
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 5000-(500*existed_sunflowers))
	{
		begin = end;
		return true;
	}
	return false;


}

bool Chronometer::timer_plant()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 5000)
	{
		begin = end;
		return true;
	}
	return false;
}

bool Chronometer::timer_zoombie()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 20000)
	{
		begin = end;
		return true;
	}
	return false;
}

bool Chronometer::move()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 1000)
	{
		begin = end;
		return true;
	}
	return false;
}

bool Chronometer::shoot()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 4500)
	{
		begin = end;
		return true;
	}
	return false;
}

bool Chronometer::refresh()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 1000)
	{
		begin = end;
		return true;
	}
	return false;
}

bool Chronometer::timer_bucketheadzoombie()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 28000)
	{
		begin = end;
		return true;
	}
	return false;
}

bool Chronometer::timer_wave()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 60000)
	{
		begin = end;
		return true;
	}
	return false;
}

void Chronometer::destroyInstance()
{
	if (instance == nullptr)
		return;
	delete instance;
	instance = nullptr;
}

Chronometer::~Chronometer()
{
}
