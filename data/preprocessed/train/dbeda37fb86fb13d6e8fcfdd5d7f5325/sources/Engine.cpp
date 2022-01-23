#include "Engine.h"

Plant* Engine::temp = nullptr;

Zombie* Engine::get_random_zombie()
{
	Zombie* z;
	srand(time(NULL));
	int r = rand()%4;
	if (r == 3)
		r = rand() % 4;
	switch (r) {
	case 0: z = new NormalZ(123, rand() % (lvl * 2 - 1) * 6 + 6 * (4 - lvl) + 1); break;
	case 1: z = new BucketHead(123, rand() % (lvl * 2 - 1) * 6 + 6 * (4 - lvl) + 1); break;
	case 2: z = new PoleVaulting(123, rand() % (lvl * 2 - 1) * 6 + 6 * (4 - lvl) + 1); break;
	case 3: z = new Super(123, rand() % (lvl * 2 - 1) * 6 + 6 * (4 - lvl) + 1); break;
	default: z = new NormalZ(123, rand() % (lvl * 2 - 1) * 6 + 6 * (4 - lvl) + 1); break;
	}
	return z;
}

Plant* Engine::get_secific_plant(COORD poz)
{
	Plant* p=nullptr;
	if (poz.X <= 12 && poz.X >= 0) {
		if (poz.Y >= 7 && poz.Y <= 12)
			p = new Sunflower(poz.X, poz.Y);
		else if (poz.Y >= 13 && poz.Y <= 18)
			p = new Nut(poz.X, poz.Y);
		else if (poz.Y >= 19 && poz.Y <= 24)
			p = new PeaShooter(poz.X, poz.Y);
		else if (poz.Y >= 25 && poz.Y <= 30)
			p = new FrozenPeaShooter(poz.X, poz.Y);
		else if (poz.Y >= 31 && poz.Y <= 36)
			p = new CherryBomb(poz.X, poz.Y);
	}
	return p;
}

bool Engine::zombie_update(int times)
{
	EntityResolver entity = EntityResolver::getInstance();
	for (auto i = 0; i < entity.zombies_list()->size(); i++)
	{
		int speed = entity.zombies_list()->at(i)->get_speed()+1;
		if (times % ((100/speed)/(((entity.plants_list()->size())/2)+1)) == 0) {
			entity.zombies_list()->at(i)->interaction();
			entity.zombies_list()->at(i)->move();
			if (entity.zombies_list()->at(i)->get_poz().X <= 12)
				return true;
		}
		if (entity.zombies_list()->at(i)->died())
			entity.delete_zombie(i);
	}
	return false;
}

void Engine::plant_update()
{
	EntityResolver entity = EntityResolver::getInstance();
	for (auto i = 0; i < entity.plants_list()->size(); i++) {
		entity.plants_list()->at(i)->interaction();
		entity.plants_list()->at(i)->snap_to_grid();
		entity.plants_list()->at(i)->draw();
		if (entity.plants_list()->at(i)->died())
			entity.delete_plant(i);
	}
}

void Engine::mouse_update()
{
	EntityResolver entity = EntityResolver::getInstance();
	Input in = Input::getInstance();
	std::pair<COORD, short> ms;
	if (temp==nullptr) {
		ms = in.get_mouse_state();
		if (ms.second == 1 && ms.first.X < 13 && ms.first.Y > 7)
		{
			temp = get_secific_plant(ms.first);
			if (!Sun::pay(temp->get_cost()))
				temp = nullptr;
		}
		if (ms.second == 1 && ms.first.X > 13 && ms.first.Y < 7) {
			for (auto i = 0; i < entity.sun_list()->size(); i++)
			{
				COORD p = ms.first;
				if (p.X % 12 != 0 || p.Y % 6 != 0)
				{
					p.X = p.X / 12 * 12 + 3;
					p.Y = p.Y / 6 * 6 + 1;
				}
				if (entity.sun_list()->at(i)->get_poz().X == p.X && entity.sun_list()->at(i)->get_poz().Y == p.Y) {
					entity.delete_sun(i);
					Sun::increase_ammount();
				}
			}
		}
	}
	else {
		ms = in.get_mouse_state();
		if (ms.second == 1 && ms.first.X > 12 && ms.first.X<121 && ms.first.Y > 6 * (4 - lvl) + 1 && ms.first.Y < (lvl * 2 - 1) * 6 + 6 * (4 - lvl) + 1) {
			bool ok = true;
			temp->set_poz(ms.first);
			for (auto i = 0; i < entity.plants_list()->size(); i++)
			{
				COORD c=entity.plants_list()->at(i)->snap_to_grid();
				COORD d=temp->snap_to_grid();
				if (c.X == d.X && c.Y == d.Y)
				{
					ok = false;
					break;
				}
			}
			if (ok == true)
			{
				entity.plants_list()->push_back(temp);
			}
			temp = nullptr;
		}
	}
	sun_ammount_update();
}

void Engine::sun_update()
{
	EntityResolver entity = EntityResolver::getInstance();
	if (entity.sun_list()->size() == 9)
		return;
	if (entity.get_time() % (30 * Sun::get_rate()) == 1)
	{
		int y = rand() % 9 * 12 + 15;
		for (int i = 0; i < entity.sun_list()->size(); i++) {
			while (y == entity.sun_list()->at(i)->get_poz().Y)
				y = rand() % 9 * 12 + 15;
			break;
		}
		Sun* s = new Sun(y, 1);
		entity.sun_list()->push_back(s);
	}

	for (int i = 0; i < entity.sun_list()->size(); i++) {
		entity.sun_list()->at(i)->draw();
	}

}

void Engine::sun_ammount_update()
{
	Output cout = Output::getInstance();
	char buff[5];
	_itoa_s(Sun::get_ammount(), buff, 10);
	std::string coco = buff; coco += "  ";
	cout.consoleUpdate( 5, 5 , { coco, 15 });
}

void Engine::border()
{
	Output cout = Output::getInstance();
	cout.consoleClear();
	for (auto i = 0; i < 138; i++)
		for (auto j = 0; j < 37; j++) {
			if ((i % 12 == 0 || j % 6 == 0 || i > 120) && (i < 13 || j < 7))
				cout.consoleUpdate( i, j , { " " , 136});
		}
	char buff[4];
	Sun* s = new Sun(3, 1);
	s->draw();
	delete s;
	Plant* p = new Sunflower(3, 7);
	p->draw();
	_itoa_s(p->get_cost(), buff, 10);
	cout.consoleUpdate( 5, 11 , { buff, 15 });
	delete p;
	p = new Nut(3, 13);
	p->draw();
	_itoa_s(p->get_cost(), buff, 10);
	cout.consoleUpdate( 5, 17 , { buff, 15 });
	delete p;
	p = new PeaShooter(3, 19);
	p->draw();
	_itoa_s(p->get_cost(), buff, 10);
	cout.consoleUpdate( 5, 23 , { buff, 15 });
	delete p;
	p = new FrozenPeaShooter(3, 25);
	p->draw();
	_itoa_s(p->get_cost(), buff, 10);
	cout.consoleUpdate( 5, 29 , { buff, 15 });
	delete p;
	p = new CherryBomb(3, 31);
	p->draw();
	_itoa_s(p->get_cost(), buff, 10);
	cout.consoleUpdate( 5, 35 , { buff, 15 });
	delete p;
}

void Engine::grid()
{
	Output cout = Output::getInstance();
	for (auto i = 0; i < 137; i++)
		for (auto j = 0; j < 37; j++) {
			if ((j % 6 == 0) && i >= 13 && j >= 6 * (4 - lvl) && j <= (lvl * 2 - 1) * 6 + 6 * (4 - lvl) + 1)
				cout.consoleUpdate( i, j , {" ", 255});
		}
}

Engine::Engine(int lvl)
{
	this->lvl = lvl;
	border();
	grid();
}

bool Engine::run()
{
	EntityResolver entity = EntityResolver::getInstance();
	Output cout = Output::getInstance();
	for (size_t i = 0; i < 600; i++)
	{
		entity.update_time(i);
		if (i % 600 == 0)
			entity.zombies_list()->push_back(get_random_zombie());
		if (zombie_update(i))
			return false;
		mouse_update();
		plant_update();
		sun_update();
		cout.consolePrint();
		Sleep(6);
	}
	return true;
}
