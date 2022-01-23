#include "ZombieList.h"



ZombieList::ZombieList()
{
	for (int i = 0; i < 200; i++)
	{
		zombie_type[i] = 0;
	}
	time_resapawn = 0;
	contor = 0;
	time_to_move = 0;
	base.X = 111;
	base.Y = 12;
	superzombie = 0;
	for (int i = 0; i < 200; i++)
	{
		vector[i] = NULL;
	}
}


int ZombieList::generate_number()
{
	int a;
	srand(time(NULL));
	a = rand() % 4;
	return a;
}

void ZombieList::generate_zombie()
{
	srand(time(NULL));
	int a = rand() % 4;
	int b = rand() % 5;
	switch (a)
	{
	case 0:
		vector[contor] = new Zombie(50, { base.X,base.Y + (short)b * 5 }, 10, 5, 0, "Zzz",30000);
		break;
	case 1:
		vector[contor] = new Zombie_PoleVaulting(50, { base.X,base.Y + (short)b * 5 }, 10, 4, 0, "|ZP|",10000);
		zombie_type[contor] = 1;
		break;
	case 2:
		vector[contor] = new Zombie_BucketHead(200, { base.X,base.Y + (short)b * 5 }, 10, 8, 0, "<ZBH^",30000);
		break;
	case 3:
		if (superzombie == 0)
		{
			vector[contor] = new Zombie_SuperZombie(200, { base.X,base.Y + (short)b * 5 }, 10, 8, 0, "<>_<>", 10000);// nu intra in superzombie
			zombie_type[contor] = 1;
			superzombie = 1;
		}
		break;
	default:
		break;
	}
	if (contor > 200)
	{
		throw Exception(2);
	}
}

void ZombieList::print()
{
	for (int i = 0; i < contor; i++)
	{
		vector[i]->print();
	}
}

void ZombieList::sterge()
{
	for (int i = 0; i < contor; i++)
	{
		vector[i]->sterge();
	}
}

void ZombieList::move_zombie()
{
	for (int i = 0; i < contor; i++)
	{
		if (vector[i] != NULL)
		{
			if (vector[i]->get_viteza() == vector[i]->get_time())
			{
				vector[i]->reset_viteza();
				if (vector[i]->get_is_eating() == 0)
				{
					COORD aux = vector[i]->get_entity_pos();
					vector[i]->sterge();
					vector[i]->set_pos({ aux.X - 1,aux.Y });
					vector[i]->print();
				}
			}
			vector[i]->increase_viteza();
		}
	}
}

void ZombieList::update_active_zombies(int pos)
{
	vector[pos] = NULL;
}

ZombieList::~ZombieList()
{
}
