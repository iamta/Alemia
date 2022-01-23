#define _CRT_SECURE_NO_WARNINGS
#include "Interactiune.h"



Interactiune::Interactiune()
{
}

coordonate Interactiune::coordonate_in_teren(int row, int col, int x_min, int x_max)
{
	coordonate punct;
	for (int j = x_min; j <= x_max; j += 12)
		for (int i = 20; i < 236; i += 24)
			if (row >= j && row <= j + 12)
				if (i <= col && col <= i + 24)
				{
					punct.x = j;
					punct.y = i;
					punct.what = TEREN;
					return punct;
				}
	return { 0, 0, NONE };
}


Interactiune::~Interactiune()
{
}

void Interactiune::Draw()
{
}

coordonate Interactiune::proximitate(int nivel)
{
	coordonate punct;
	std::string action = UserInterface::ConsoleInput::getInstance().getUserActions();
	int row = 0, col = 0, ok = 0;
	if (action != "") {
		if (!strstr(action.c_str(), "double"))
			return { 0,0, NONE};
		char* poz = _strdup(action.c_str());
		char*tok = strtok(poz, "(");
		if (tok != NULL)
		{
			tok = strtok(NULL, ",");
			if (tok)
				col = atoi(tok);
			tok = strtok(NULL, ")");
			if (tok)
				row = atoi(tok);
			if (row*col)
				ok = 1;
		}

		if (ok)
			for (int i = 4; i < 65; i += 12)
				if (i < row&&row < i + 12)
					if (0 <= col && col <= 20)
					{
						punct.x = i;
						punct.y = 0;
						punct.what = PLANTA;
						return punct;
					}
		if (ok)
			for (int i = 20; i < 236; i += 24)
				if (row > 0 && row < 4)
					if (col > i&&col < i + 24)
					{
						punct.x = 0;
						punct.y = i;
						punct.what = SOARE;
						return punct;
					}
		switch (nivel)
		{
		case 1:
			return coordonate_in_teren(row, col, 28, 40);
			break;
		case 2:
			return coordonate_in_teren(row, col, 16, 52);
			break;
		case 3:
			return coordonate_in_teren(row, col, 4, 64);
			break;
		}

	}
	return { 0,0, NONE };
}

coordonate::coordonate(coordonate &&bla)
{
	x = bla.x;
	y = bla.y;
	what = bla.what;
}
