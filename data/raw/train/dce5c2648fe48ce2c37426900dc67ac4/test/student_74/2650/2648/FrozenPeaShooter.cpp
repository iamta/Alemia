#include "FrozenPeaShooter.h"
#include "EntityResolver.h"
FrozenPeaShooter::FrozenPeaShooter(SHORT X, SHORT Y):Plant(X, Y)
{
	set_cost(150);
	set_damage(20);
	set_hp(120);
	set();
}
void FrozenPeaShooter::interaction()
{
	EntityResolver entity = EntityResolver::getInstance();
	if (entity.get_time()%100==0)
	{
		for (auto i = 0; i < entity.zombies_list()->size(); i++)
		{
			if (entity.zombies_list()->at(i)->get_poz().Y == get_poz().Y)
			{
				Frozen* one = new Frozen(get_poz().X + 1, get_poz().Y + 2, get_damage());
				bulets.push_back(one);
			}
		}
	}
	for (auto i = 0; i < bulets.size() && entity.get_time() % 5 == 0; i++) {
		bulets[i]->move();
		bulets[i]->interaction();
		bulets[i]->slow();
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

void FrozenPeaShooter::set()
{
	if (box_content()->size() == 0) {
		box_content()->push_back({ "",15 });
		box_content()->push_back({ "",15 });
		std::string line = "(.";	line += (char)249;	line += "O";
		box_content()->push_back({ line, 3 });
		box_content()->push_back({ "_)" , 10 });
		box_content()->push_back({ "",15 });
	}
}
