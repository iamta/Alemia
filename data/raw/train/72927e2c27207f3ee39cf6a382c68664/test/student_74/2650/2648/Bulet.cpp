#include "Bulet.h"
#include "EntityResolver.h"

Bulet::Bulet(SHORT X, SHORT Y, int dmg)
{
	set_poz({ X, Y });
	set_hp(1);
	set_damage(dmg);
}

void Bulet::draw()
{
	Output cout = Output::getInstance();
	for (auto i = 0; i < box_content()->size(); i++) {
		COORD p = get_poz();
		cout.consoleUpdate(p.X, p.Y + i , { box_content()->at(i).first, box_content()->at(i).second });
	}
}

void Bulet::move()
{
	set_poz({ get_poz().X + 1,get_poz().Y });
	if (get_poz().X > 123)
	{
		set_hp(-1);
	}
	draw();
	delete_tail();
}

void Bulet::delete_tail()
{
	Output cout = Output::getInstance();
	cout.consoleUpdate(get_poz().X - 1, get_poz().Y , { " " , 15});
}

void Bulet::interaction()
{
	EntityResolver entity = EntityResolver::getInstance();
	for (auto i = 0; i < entity.zombies_list()->size(); i++)
	{
		if (entity.zombies_list()->at(i)->get_poz().X + 2 >= get_poz().X &&
			entity.zombies_list()->at(i)->get_poz().X <= get_poz().X &&
			entity.zombies_list()->at(i)->get_poz().Y == get_poz().Y - 2)
		{
			entity.zombies_list()->at(i)->set_hp(entity.zombies_list()->at(i)->get_hp() - get_damage());
			set_hp(-1);
		}
	}
}
