#include "Sun.h"



Sun::Sun():Resurse()
{
	old.X = 0;
	old.Y = 0;
	selected = 0;
}

Sun::Sun(int x, int y) : Resurse(50, {(short) x,(short) y},'$')
{
	old.X = x;
	old.Y = y;
	selected = 0;
}


Sun::~Sun()
{
}
