#include "Entity.h"



Entity::Entity()
{
	health = 0;
	pos.X = 0;
	pos.Y = 0;
}

Entity::Entity(int health,COORD A)
{
	this->health = health;
	this->pos.X = A.X;
	this->pos.Y = A.Y;
}

void Entity::print()
{
	
}

void Entity::sterge()
{
}

void Entity::set_pos(COORD other)
{
	pos.X = other.X;
	pos.Y = other.Y;
}

int Entity::get_cost()
{
	return 0;
}

char Entity::get_char()
{
	return 0;
}

int Entity::get_damage()
{
	return 0;
}

int Entity::get_viteza()
{
	return 0;
}



void Entity::increase_viteza()
{
	
}

int Entity::get_rezistenta()
{
	return 0;
}

void Entity::update_life(int x)
{
	health -=x;
}

void Entity::update_speed(int x)
{

}

void Entity::increase_time()
{
}

void Entity::reset_time()
{
}

int Entity::get_time()
{
	return 0;
}

void Entity::reset_viteza()
{
}

void Entity::set_is_eating(int i)
{
}

int Entity::get_is_eating()
{
	return 0;
}

void Entity::set_is_jumped(int i)
{
}

int Entity::get_is_jumped()
{
	return 0;
}


Entity::~Entity()
{
}
