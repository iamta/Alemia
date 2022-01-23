#include "Resources.h"
#include "ConsoleOutput.h"
#include "Chronometer.h"
#include<random>
static ConsoleOutput&conOut = ConsoleOutput::getInstance();





Resources::Resources()
{
	for (int i = 0; i < 9; i++)
	{
		free_spaces[i] = 1;
	}
}

void Resources::Generate_sun(int existed_sunflowers)
{
	int pos = 10;
	for (int i = 0; i < 9; i++)
	{
		
		sun_positioning[i] = pos;
		pos += 6;
	}
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type>dist9(0, 8);
	int num = dist9(rng);
	
	if (Chronometer::getInstance().timer_sun(existed_sunflowers))
	{
		int i = num;
		if (free_spaces[i])
		{
			conOut( sun_positioning[i],3) << sun;
			free_spaces[i] = 0;
		}
		
	}

}

bool Resources::check_resource(int x)
{
	for (int i = 0; i < 9; i++)
	{
		if ((sun_positioning[i] == x) && (free_spaces[i] == 0))
		{
			free_spaces[i] = 1;
			conOut(x, 3) << " ";
			return true;
		}
	}
	return false;

}


Resources::~Resources()
{
}


