#include "Zombie.h"

Zombie::Zombie(int heal,int demage,const string forma)
{
	x = 0;
	y = 0;
	this->heal = heal;
	this->demage = demage;
	this->forma= forma;
	timp.start();
	move = true;
}

Zombie::~Zombie()
{
}

bool Zombie::GetMove()
{
	return move;
}

void Zombie::SetMove(bool move)
{
	this->move = move;
}

int Zombie::GetTimp()
{
	return timp.elapsedTime();
}

void Zombie::SetX(int x)
{
	this->x = x;
}

void Zombie::SetY(int y)
{
	this->y = y;

}

void Zombie::SetName(string name)
{
	this->name = name;
}

void Zombie::SetHeal(int heal)
{
	this->heal = heal;
}

void Zombie::SetDemage(int demage)
{
	this->demage = demage;
}

void Zombie::SetForma(string forma)
{
	this->forma = forma;
}

int Zombie::GetX()
{
	return x;
}

int Zombie::GetY()
{
	return y;
}

string Zombie::GetName()
{
	return name;
}

int Zombie::GetHeal()
{
	return heal;
}

int Zombie::GetDemage()
{
	return demage;
}

string Zombie::GetForma()
{
	return forma;
}
