#pragma once
#include "EntityResolver.h"
#include "Output.h"
#include "Input.h"
#include "NormalZ.h"
#include "BucketHead.h"
#include "Super.h"
#include "PoleVaulting.h"
#include "PeaShooter.h"
#include "FrozenPeaShooter.h"
#include "Nut.h"
#include "Sunflower.h"
#include "CherryBomb.h"
#include "Sun.h"
#include <time.h>

class Engine
{
	static Plant* temp;
	int lvl=3;
	Zombie* get_random_zombie();
	Plant* get_secific_plant(COORD);
	bool zombie_update(int);
	void plant_update();
	void mouse_update();
	void sun_update();
	void sun_ammount_update();
	void border();
	void grid();
public:
	Engine(int lvl);
	void set_lvl(int lvl) { this->lvl = lvl; }
	int get_lvl() { return lvl; }
	bool run();
};

