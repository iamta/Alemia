#pragma once
# include "Block.h"
class Grid
{
	Block cube;
	vector<Block> cage;
public:
	Grid();
	Grid(int x, int y);
	void print_cage();
	void change_core(int linie,int col,char c);
	vector<Block> get_cage() { return cage; }

	virtual~Grid();
	//friend class block;
};

