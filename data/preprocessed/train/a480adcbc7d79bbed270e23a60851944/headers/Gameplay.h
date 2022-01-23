#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Block.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include "Entity.h"
#include "Plant.h"
#include "Peashooter.h"
#include "Wall_nut.h"
#include "Sunflower.h"
#include "Chery_Bomb.h"
#include "Snow_pea.h"
#include "Plantlist.h"
#include "Resurse.h"
#include "Sun.h"
#include "SunList.h"
#include "Money.h"
#include "Bullet.h"
#include "Bullet_normal.h"
#include "Bullet_frozen.h"
#include "BulletList.h"
#include "Zombie.h"
#include "Zombie_BucketHead.h"
#include "Zombie_PoleVaulting.h"
#include "Zombie_SuperZombie.h"
#include "ZombieList.h"
#include "time.h"
#include "Logfile.h"
#include "Exception.h"
class Gameplay
{
public:
	Gameplay();
	void check_if_bullet_hit_zombie(ZombieList&Z, BulletList&B);
	void check_if_zombie_hit_plant(PlantList&P, ZombieList&Z, BulletList&B);
	void intro_game();
	void end_game(Logfile &L);
	void check_end_game(ZombieList&Z, Logfile&L);
	void check_bullets_and_plants(BulletList&B, PlantList&P);

	void game();

	virtual~Gameplay();
};

