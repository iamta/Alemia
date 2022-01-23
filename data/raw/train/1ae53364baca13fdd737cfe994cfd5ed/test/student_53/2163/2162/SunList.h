#pragma once
#include "Sun.h"
#include "Resurse.h"
#include "time.h"
class SunList
{
	Sun Sori[9];
	int index;
	int time_respawn;
	int remember;

public:
	SunList();
	SunList(short x, short y);
	void print_sunlist();
	int  generate_random_pos();
	void increase_time_spawn() { time_respawn++; };
	void select_index();
	int get_time_respawn() { return time_respawn; }
	void set_time_respawn_to_null() { time_respawn = remember; }
	Sun* get_Sori() { return Sori; }
	int& get_remember() { return remember; }
	
	virtual~SunList();
};

