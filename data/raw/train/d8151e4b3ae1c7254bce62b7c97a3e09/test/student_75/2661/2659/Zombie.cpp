#define _CRT_SECURE_NO_WARNINGS
#include "Zombie.h"

using namespace Oaspete;
enum ZOMBIE_SITUATION;


Zombie::Zombie()
{
	get_viata() = 15;
	set_Culoare("\u001b[32m");
	set_Desen("\\_(*!*)_/ ");
	type = S;
	coord = { 0, 225, ZOMBIE, NO };
	Ice_shot = false;
	Jump = false;
}

Zombie::~Zombie()
{
}

void Zombie::Draw(coordonate &where)
{
	UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y) << culoare;
	UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y) << desen;
	UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y) << "\u001b[37m";
}

void Zombie::set_Culoare(const char *aux)
{
	strcpy(culoare, aux);
}

void Zombie::set_Desen(const char *aux)
{
	strcpy(desen, aux);
}

bool Oaspete::Zombie::actualizeaza_Zombie()
{
	if (coord.y == 20)
		return true;
	coord.y--;
	return false;
}

void Oaspete::Zombie::unDraw(coordonate &where)
{
	UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y) <<"          ";
}
