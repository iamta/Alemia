#include "Resurse.h"



Resurse::Resurse()
{
	cost = 0;
	res_pos.X = 0;
	res_pos.Y = 0;
	C = 'U';
}

Resurse::Resurse(int cost_1, COORD res_pos_1, char C_1)
{
	cost = cost_1;
	res_pos.X = res_pos_1.X;
	res_pos.Y = res_pos_1.Y;
	C = C_1;
}

void Resurse::printf()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), res_pos);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << C;
}


void Resurse::sterge()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 00);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), res_pos);
	std::cout << "  ";
}

Resurse::~Resurse()
{
}
