#include "BulletList.h"



BulletList::BulletList()
{
	contor = 0;
	bullets[0] = new Bullet_normal();
	bullets[1] = new Bullet_frozen();
	for (int i = 0; i < 300; i++)
	{
		active_bullets[i] = NULL;
	}
}


void BulletList::add_bulet_to_list(Bullet * aux)
{
	active_bullets[contor] = aux;
	if (contor > 300)
	{
		throw Exception(1);
	}
}

void BulletList::add_bullet_type_to_list(int i)
{
	bullet_type[contor] = i;
}

void BulletList::update_curent_bullet_position()
{
	for (int i = 0; i < contor; i++)
	{
		if (active_bullets[i] != NULL)
		{
			active_bullets[i]->increase_X_coord();
		}
	}
}

void BulletList::print_bullet_list()
{
	for (int i = 0; i< contor; i++)
	{
		if (active_bullets[i] != NULL)
		{
			active_bullets[i]->print();
		}
	}
}

void BulletList::delete_bullet_list()
{
	for (int i = 0; i < contor; i++)
	{
		if (active_bullets[i] != NULL)
		{
			active_bullets[i]->sterge();
		}
	}
}

void BulletList::check_bullet_pos()
{
	for (int i = 0; i < contor; i++)
	{
		if (active_bullets[i] != NULL)
		{
			if (active_bullets[i]->get_bullet_pos().X == 111)
			{
				active_bullets[i]->sterge();
				active_bullets[i]->reset_bullet_poss();

			}
		}
	}
}

void BulletList::update_active_bullets(int i)
{
	active_bullets[i] = NULL;
	bullet_type[i] = 3;
}

BulletList::~BulletList()
{
}
