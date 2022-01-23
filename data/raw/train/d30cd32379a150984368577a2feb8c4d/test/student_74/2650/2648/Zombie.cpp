#include "Zombie.h"

Zombie::Zombie(SHORT x, SHORT y)
{
	set_poz({ x, y });
	set_hp(100);
	set_damage(10);
	set_speed(2);
	set_base_speed(2);
}

void Zombie::draw()
{
	Output cout = Output::getInstance();
	for (auto i = 0; i < box_content()->size(); i++) {
		COORD p = get_poz();
		cout.consoleUpdate(p.X, p.Y + i , { box_content()->at(i).first, box_content()->at(i).second });
	}
}

void Zombie::move()
{
	draw();
	delete_trail();
	if (speed != 0) {
		set_poz({ get_poz().X - 1, get_poz().Y });
	}
}

void Zombie::delete_trail()
{
	Output cout = Output::getInstance();
	for (auto i = 0; i < box_content()->size(); i++)
		cout.consoleUpdate( get_poz().X + box_content()->at(i).first.size(), get_poz().Y + i , { " ", 15});
}
