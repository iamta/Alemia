#pragma once
#include "Entity.h"
#include <string>
class Zombie: public Entity
{
	string name;
	int damage;
	int rezistenta;
	int viteza;
	int time;
	int is_eating;
public:
	Zombie();
	Zombie(int health, COORD A, int damage, int rezistenta, int viteza, string name,int time);
	 int get_damage() { return damage; }
	 int get_viteza() { return viteza; }
	 int get_rezistenta() { return rezistenta; }
	 string get_name() { return name; }
	 void print();
	 void increase_time() { time++; }
	 void reset_time() { time = 0; }
	 int get_time() { return time; }
	 void update_speed(int x);
	 void update_life(int x);
	 void increase_viteza() { viteza++; };
	 void reset_viteza() { viteza = 0; }
	 void set_is_eating(int i);
	 int get_is_eating();
	 void sterge();
	virtual~Zombie();
};

