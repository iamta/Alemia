#include "PeaShooter.h"
#include "EntityResolver.h"

PeaShooter::PeaShooter(SHORT X, SHORT Y) :Plant(X, Y)
{
	set_cost(100);
	set_damage(15);
	set();
}

void PeaShooter::interaction()
{
	EntityResolver entity = EntityResolver::getInstance();
	if (entity.get_time() % 100 == 0)
	{
		for (auto i = 0; i < entity.zombies_list()->size(); i++)
		{
			if (entity.zombies_list()->at(i)->get_poz().Y == get_poz().Y)
			{
				NormalB* one = new NormalB(get_poz().X + 1, get_poz().Y + 2, get_damage());
				bulets.push_back(one);
			}
		}
	}
	for (auto i = 0; i < bulets.size() && entity.get_time() % 10 == 0; i++) {
		bulets[i]->move();
		bulets[i]->interaction();
		if (bulets[i]->died())
		{
			bulets[i]->box_content()->at(0).first = " ";
			bulets[i]->draw();
			for (auto j = i; j < bulets.size() - 1; j++)
				bulets[j] = bulets[j + 1];
			bulets.pop_back();
		}
	}
}

void PeaShooter::set()
{
	if (box_content()->size() == 0) {
		box_content()->push_back({ "",15 });
		box_content()->push_back({ "",15 });
		std::string line = "(.";	line += (char)249;	line += "O";
		box_content()->push_back({ line, 10 });
		box_content()->push_back({ "_)" , 10 });
		box_content()->push_back({ "",15 });
	}
}
