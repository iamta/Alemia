#include "Zombie.h"



Zombie::Zombie()
{
	name = "zzz";
	damage = 0;
	rezistenta = 0;
	viteza = 0;
	time = 0;
	is_eating = 0;
}

Zombie::Zombie(int health, COORD A, int damage, int rezistenta, int viteza, string name,int time):Entity(health,A)
{
	this->damage = damage;
	this->rezistenta = rezistenta;
	this->viteza = viteza;
	this->name = name;
	this->time = time;
	is_eating = 0;
}


void Zombie::print()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { pos.X,pos.Y });
	std::cout << name;
}

void Zombie::update_speed(int x)
{
	time += x;
}

void Zombie::update_life(int x)
{
	health = health - (x - rezistenta);
}

void Zombie::set_is_eating(int i)
{
	is_eating = i;
}

int Zombie::get_is_eating()
{
	return is_eating;
}

void Zombie::sterge()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { pos.X,pos.Y });
	std::cout <<"     ";
}

Zombie::~Zombie()
{
}
