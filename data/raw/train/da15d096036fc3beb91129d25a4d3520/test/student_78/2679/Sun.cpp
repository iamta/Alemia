
#include "Sun.h"

Sun* Sun::SunFactory()
{
	int x = (rand() % 8 + 2) * 10;

	return new Sun(x);
}
int Sun::SunCounter = 0;
void Sun::draw()
{
	 UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	 conOut(x, y)<< "*";
}
void Sun::addSun(int s)
{
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	SunCounter += s;
	conOut(1, 1) << "Sun :              ";
	conOut(1, 1) << "Sun : " << SunCounter << "\n Score : ";
}

int Sun::getSunCounter()
{
	return SunCounter;
}

Sun::Sun(int a)
{
	x = a;
	
	draw();
}
void Sun::update()
{
	
}

Sun::~Sun()
{
	UserInterface::ConsoleOutput::getInstance(x,y) << " ";
}
