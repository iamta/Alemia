#include "Plant.h"


Plant::Plant()
{
}

Plant::Plant(char c_1, int health, COORD A,int cost_1):Entity(health,A)
{
	c = c_1;
	cost = cost_1;
}

void Plant::print()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	cout << c;
}

void Plant::sterge()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 00);
	cout << " ";
}




Plant::~Plant()
{
}
