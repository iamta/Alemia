#pragma once
#include "Plant.h"
#include "Zombie.h"
#include "Sun.h"
class EntityResolver
{
	static std::vector<Plant*> plants;
	static std::vector<Zombie*> zombies;
	static std::vector<Sun*> sunny;
	static  EntityResolver* reference;
	static int time;
	EntityResolver() {}
public:
	static EntityResolver& getInstance();
	std::vector<Plant*>* plants_list() { return &plants; }
	std::vector<Sun*>* sun_list() { return &sunny; }
	std::vector<Zombie*>* zombies_list() { return &zombies; }
	void update_time(int);
	int get_time() { return time; }
	void delete_plant(int);
	void delete_zombie(int);
	void delete_sun(int);
};

