#include "Finante.h"

Finante *Finante::Instance = nullptr;

Finante::Finante()
{
	money = 0;

}

Finante & Finante::getInstance()
{
	if (Instance == nullptr)
	{
		Instance = new Finante;
	}
	return *Instance;
}

void Finante::destroyInstance()
{
	if (Instance != nullptr)
	{
		delete(Instance);
	}
	Instance = nullptr;
}

void Finante::addMoney(int x)
{
	money += x;
}

int Finante::getMoney()
{
	return money;
}

void Finante::withdrawMoney(int sum)
{
	money -= sum;
}
