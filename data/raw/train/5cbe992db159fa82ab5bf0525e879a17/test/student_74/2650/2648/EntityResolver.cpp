#include "EntityResolver.h"

EntityResolver* EntityResolver::reference = nullptr;
std::vector<Zombie*> EntityResolver::zombies;
std::vector<Plant*> EntityResolver::plants;
std::vector<Sun*> EntityResolver::sunny;
int EntityResolver::time;

EntityResolver& EntityResolver::getInstance()
{
	if (reference == nullptr) {
		reference = new EntityResolver();
	}
	return *reference;
}

void EntityResolver::update_time(int t)
{
	time = t;
}

void EntityResolver::delete_plant(int index)
{
	plants[index]->empty_box();
	plants[index]->draw();
	plants[index]->clear();
	for (auto i = index; i < plants.size() - 1; i++)
		plants[i] = plants[i + 1];
	plants.pop_back();
}

void EntityResolver::delete_zombie(int index)
{
	zombies[index]->empty_box();
	zombies[index]->draw();
	zombies[index]->clear();
	for (auto i = index; i < zombies.size() - 1; i++)
		zombies[i] = zombies[i + 1];
	zombies.pop_back();
}

void EntityResolver::delete_sun(int index)
{
	sunny[index]->empty_box();
	sunny[index]->draw();
	sunny[index]->clear();
	for (auto i = index; i < sunny.size() - 1; i++)
		sunny[i] = sunny[i + 1];
	sunny.pop_back();
}
