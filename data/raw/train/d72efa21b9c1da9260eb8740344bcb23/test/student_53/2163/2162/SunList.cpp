#include "SunList.h"

SunList::SunList()
{
	time_respawn = 0;
	index = 0;
	remember = 0;
}

SunList::SunList(short x, short y)
{
	index = 0;
	time_respawn = 0;
	remember = 0;
	short X = x;
	for (int i = 0; i < 9; i++)
	{
		Sori[i].set_res_pos({ X,y });
		X += 11;
	}
}

void SunList::print_sunlist()
{
	for (int i = 0; i < 9; i++)
	{
		Sori[i].printf();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int SunList::generate_random_pos()
{
	srand(time(NULL));
	int a = rand() % 9;
	return a;
}

void SunList::select_index()
{
		int held = 0;
		for (int i = 0; i < 9; i++)
		{
			if (Sori[i].get_selcted() == 1)
			{
				held++;
			}
		}
		if (held == 9)
		{
			return;
		}
		index = generate_random_pos();
		if (Sori[index].get_selcted() == 1)
		{
			for (int i = 0; i < 9; i++)
			{
				if (Sori[i].get_selcted() == 0)
				{
					index = i;
					Sori[index].set_selected(1);
					Sori[index].printf();
					break;
				}
			}
		}
		else
		{
			Sori[index].set_selected(1);
			Sori[index].printf();
		}
		
		return;
}


SunList::~SunList()
{
}
