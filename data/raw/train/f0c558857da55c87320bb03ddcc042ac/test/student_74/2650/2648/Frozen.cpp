#include "Frozen.h"
#include "EntityResolver.h"
Frozen::Frozen(SHORT X, SHORT Y, int dmg):Bulet(X, Y, dmg)
{
	set();
}

void Frozen::set()
{
	if (box_content()->size() == 0) {
		box_content()->push_back({ "*" , 3 });
	}
}

void Frozen::slow()
{
	EntityResolver entity = EntityResolver::getInstance();
	for (auto i = 0; i < entity.zombies_list()->size(); i++)
	{
		if (entity.zombies_list()->at(i)->get_poz().Y <= get_poz().Y + 1)
		{
			if(entity.zombies_list()->at(i)->get_speed() == entity.zombies_list()->at(i)->get_base_speed()&& entity.zombies_list()->at(i)->get_speed()>=1)
				entity.zombies_list()->at(i)->set_speed(entity.zombies_list()->at(i)->get_base_speed()/2);
		}
	}
}
