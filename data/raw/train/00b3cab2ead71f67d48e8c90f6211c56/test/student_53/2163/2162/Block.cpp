#include "Block.h"



Block::Block()
{
	string line = "_ _ _ _ _";
	B.push_back(line);
	line = "|       |";
	for (int i = 0; i < 3; i++)
		B.push_back(line);
	line = "- - - - -";
	A.X = 5;
	A.Y = 5;
	M.X = A.X + 4;
	M.Y = A.Y + 2;
}

Block::Block(int x, int y)
{
	string line = "_ _ _ _ _";
	B.push_back(line);
	line = "|       |";
	for (int i = 0; i < 3; i++)
		B.push_back(line);
	line = "- - - - -";
	B.push_back(line);
	A.X = x;
	A.Y = y;
	M.X = A.X + 4;
	M.Y = A.Y + 2;
	x_reset = x;
	y_reset = y;
}

void Block::print()
{
	COORD aux{ A.X,A.Y };
	for (int i = 0; i < 5; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { aux.X,aux.Y });
		cout << B[i];
		aux.Y++;
	}
}


void Block::change_mijloc(char c)
{
	B[2][4] = c;
}

 Block::~Block()
{
}
