#pragma once
#include "Entity.h"
#include "Zombie.h"
#include "Zombie_BucketHead.h"
#include "Zombie_PoleVaulting.h"
#include "Zombie_SuperZombie.h"
#include <time.h>
#include "Exception.h"
class ZombieList
{
	Entity * vector[200];
	int zombie_type[200];
	int contor;
	int time_resapawn;
	int time_to_move;
	int superzombie;
	COORD base;
public:
	ZombieList();
	Entity** get_vector() { return vector; }
	int generate_number();
	void generate_zombie();
	int * get_zombie_type() { return zombie_type; }
	void print();
	void sterge();
	void move_zombie();
	void increase_time_to_move() { time_to_move++; }
	void reset_time_to_move() { time_to_move = 4000; }
	int get_time_to_move() { return time_to_move; }
	void increase_contor() { contor++; }
	void increase_time_respawn() { time_resapawn++; }
	int get_contor() { return contor; }
	int get_time_respawn() { return time_resapawn; }
	void reset_time_respawn() { time_resapawn = 0; }
	void update_active_zombies(int pos);
	virtual~ZombieList();
};