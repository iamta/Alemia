#include "Money.h"

Money::Money()
{
	money = 50;
}

Money::~Money()
{
}

int Money::GetMoney()
{
	return money;
}

void Money::SetMoney(int mon)
{
	money  = mon+money;
}
