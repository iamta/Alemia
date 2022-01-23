#include "Money.h"



Money::Money()
{
	money = 100;
}

void Money::print_money()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,7 });
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << money;
}

void Money::sterge_money()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,7 });
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 00);
	std::cout << "     ";
}


Money::~Money()
{
}
