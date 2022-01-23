#pragma once
# include <iostream>
# include <string>
# include <vector>
# include <Windows.h>
class Resurse
{
protected:
	int cost;
	COORD res_pos;
	char C;

public:
	Resurse();
	Resurse(int cost_1, COORD res_pos_1, char C_1);
	void printf();
	COORD get_coord() { return res_pos; }
	void set_res_pos(COORD pos){ res_pos.X = pos.X; res_pos.Y = pos.Y; }
	void sterge();
	
	virtual~Resurse();
};

