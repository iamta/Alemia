#include "CherryBomb.h"
#include "EntityResolver.h"
CherryBomb::CherryBomb(SHORT x, SHORT y) :Plant(x, y)
{
	set_cost(75);
	set_hp(1);
	set_damage(300);
	set();
}

void CherryBomb::interaction()
{
	EntityResolver entity = EntityResolver::getInstance();
	Output cout = Output::getInstance();
	for (auto i = 0; i < entity.zombies_list()->size(); i++) {
		for (auto j = -7; j <= 7; j++)
			for (auto k = -13; k <= 18; k++) {
				//cout(get_poz().X + k, get_poz().Y + j) << "H";
				if (entity.zombies_list()->at(i)->get_poz().X == get_poz().X + k && entity.zombies_list()->at(i)->get_poz().Y == get_poz().Y + j) {
					entity.zombies_list()->at(i)->set_hp(entity.zombies_list()->at(i)->get_hp() - get_damage());
				}
			}
	}
	if (entity.get_time() % 100 == 0)
	{
		set_hp(-1);
		for (auto j = -7; j <= 7; j++)
			for (auto k = -13; k <= 18; k++)
				if (get_poz().X + k > 13 && get_poz().X + k < 122 && get_poz().Y + j>6 && get_poz().Y + j < 36)
				{
					cout.consoleUpdate(get_poz().X + k, get_poz().Y + j, { "H", 15 });
					
				}
		cout.consolePrint();
		for (auto j = -7; j <= 7; j++)
		{
			for (auto k = -13; k <= 18; k++)
				if (get_poz().X + k > 12 && get_poz().X + k < 122 && get_poz().Y + j>6 && get_poz().Y + j < 36) {
					unsigned char nr = 0;
					if ((get_poz().Y + j) % 6 != 0)
						nr = 15;
					else nr = 255;
					cout.consoleUpdate(get_poz().X + k, get_poz().Y + j, { " ", nr });
					
				}
			cout.consolePrint();
		}
	}
}

void CherryBomb::set()
{
	if (box_content()->size() == 0) {
		box_content()->push_back({ "",15 });
		box_content()->push_back({ "  /{_7" , 10 });
		box_content()->push_back({ " /  \\" , 10 });
		box_content()->push_back({ "(`)(`)" , 4 });
		box_content()->push_back({ "",15 });
	}
}
