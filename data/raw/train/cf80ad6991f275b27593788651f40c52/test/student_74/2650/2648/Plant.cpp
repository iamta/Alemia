#include "Plant.h"

Plant::Plant(SHORT X, SHORT Y)
{
	cost = 100;
	set_poz({ X, Y });
	set_damage(0);
	set_hp(100);
}

void Plant::draw()
{
	Output cout = Output::getInstance();
	for (auto i = 0; i < box_content()->size(); i++) {
		COORD p = get_poz();
		cout.consoleUpdate(p.X, p.Y + i, { box_content()->at(i).first, box_content()->at(i).second});
	}
}

COORD Plant::snap_to_grid()
{
	COORD p = get_poz();
	if (p.X % 12 != 0 || p.Y % 6 != 0)
	{
		p.X = p.X / 12 * 12+2;
		p.Y = p.Y / 6 * 6+1;
	}
	set_poz(p);
	return p;
}
