#pragma once
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
class Entity
{
protected:
	int health;
	COORD pos;
public:
	Entity();
	Entity(int health,COORD A);
	virtual void print();
	virtual void sterge();
	virtual void set_pos(COORD other);
	virtual int get_cost();
	virtual char get_char();
	virtual int get_damage();
	virtual int get_viteza();
	virtual void increase_viteza();
	int get_health() { return health; }
	virtual int get_rezistenta();
	virtual void update_life(int x);
	virtual void update_speed(int x);
	virtual void increase_time();
	virtual void reset_time();
	virtual int get_time();
	virtual void reset_viteza();
	virtual void set_is_eating(int i);
	virtual int get_is_eating();
	virtual void set_is_jumped(int i);
	virtual int get_is_jumped();
	COORD get_entity_pos() { return pos; };
	virtual~Entity();
};