#pragma once
#include "Plant.h"
#include "Entity.h"
#include "Sunflower.h"
#include "Wall_nut.h"
#include "Peashooter.h"
#include "Snow_pea.h"
#include "Chery_Bomb.h"
#include "SunList.h"
#include <vector>
#include "Exception.h"

class PlantList
{
	Entity* vector[5];//libraria de selectei a plantlor
	Entity* active_plants[100];
	int plant_type[100];
	int CB_index;
	static int contor;
public:
	PlantList();
	Entity** get_vector() { return vector; }
	Entity** get_active_plants() { return active_plants; }
	static void increase_contor() { contor++; }
	void get_plant(int i);
	Entity* get_temp(int i);
	void put_it_inside(Entity* temp);
	void print();
	void update_curent_object(COORD mouse_pos);
	void print_curent_object();
	void update_active_plants(int i);
	int get_CB_index() { return CB_index; }
	void reset_CB_index() { CB_index = 0; }
	static int get_contor() { return contor; }
	virtual~PlantList();
};