#include "Grid.h"


Grid::Grid()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cage.push_back(cube);
			cube.increase_x();
			cube.update_mijloc();
		}
		cube.increase_y();
		cube.reset_x();
		cube.update_mijloc();
	}
}

Grid::Grid(int x, int y)
{
	Block cube(x, y);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{

			cage.push_back(cube);

			cube.increase_x();
			cube.update_mijloc();
		}
		cube.increase_y();
		cube.reset_x();
		cube.update_mijloc();
	}
}

void Grid::print_cage()
{
	for (int i = 0; i < 45; i++)
	{
		cage[i].print();
	}
}

void Grid::change_core(int linie,int col,char c)
{
	cage[linie* 9 + col].change_mijloc(c);
}


Grid::~Grid()
{
}
