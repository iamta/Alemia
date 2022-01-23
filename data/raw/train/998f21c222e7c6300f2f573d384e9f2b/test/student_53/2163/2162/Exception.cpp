#include "Exception.h"



Exception::Exception()
{
}

Exception::Exception(int num)
{
	x = num;
}

void Exception::judge_me()
{
	if (x == 0)
	{
		cout << "You cant get any more plants\n";
	}
	if (x == 1)
	{
		cout << "Bullets overflow! TO MAY BULLETS\n";
	}
	if (x >= 4)
	{
		cout << "Undefined exceptions\n";
	}
	if (x == 2)
	{
		cout << "Zombies overflow !";
	}
	if (x == 3)
	{
		cout << "Problems with zombies and plnats\n";
	}
}


Exception::~Exception()
{
}
