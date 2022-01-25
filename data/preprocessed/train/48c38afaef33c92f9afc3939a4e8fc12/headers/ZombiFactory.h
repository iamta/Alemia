#pragma once
#include "Zombi.h"
#include <map>
#include <unordered_map>
#include <chrono>
#include <time.h>
#include <stdlib.h>
enum ZombiFactoryStrategy
{
	// returneaza la fiecare pas unul sau niciunu zombi
	INCREMENTAL_MORE
};
// La fiecare pas clasa GameStateMachine apeleaza CreateNewZombie
// Aceasta clasa va mentine un state intern cu timpul scurs si va returna zombi
// cand runda va avansa
class ZombiFactory
{
	static ZombiFactoryStrategy _current_stretegy;
	static chrono::high_resolution_clock::time_point _time;
	static std::map<int,int>::iterator index;
	static const int TIME_BETWEEN_NEW_ZOMBI_APPEARS = 10000;
	static std::map<int, int> _map_cycles_L1;
	static map<int,vector< Zombi*>> _map_predefined_zombi;
	static vector< Zombi*> _array_predefinde_zolmbies_L2;
	static int _level;
public:
	static void  Init(ZombiFactoryStrategy strategy, int level = 1)
	{
		_current_stretegy = strategy;
		_time = chrono::high_resolution_clock::now();
		_level = level;
	}
	static Zombi* CreateNewZombie()
	{
		auto new_time_update = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(new_time_update - _time).count();

		if (index->second <= 0)
			index = std::prev(index);
		if (duration > index->first)
		{
			index->second--;
			_time = chrono::high_resolution_clock::now();
			return GetZombiByLevel(_level);
		}
		return nullptr;
	}
	static Zombi* GetZombiByLevel(int level)
	{
		auto zombi_array = _map_predefined_zombi[level];
		auto size = zombi_array.size();
		srand(time(NULL));
		int index = rand() % size;
		return zombi_array[index];

	}
};

