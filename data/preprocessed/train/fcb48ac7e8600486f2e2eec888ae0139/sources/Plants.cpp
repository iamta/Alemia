#include "Plants.h"

plants::plants()
{
	delay = 0;
}

void plants::StarTimp()
{
	timp.start();
}

int plants::GetTimp()
{
	return timp.elapsedTime();
}

void plants::SetPrint(bool print)
{
	this->print = print;
}

bool plants::GetPrint()
{
	return print;
}

void plants::SetX(int x)
{
	this->x = x;
}

void plants::SetDelay(int delay)
{
	this->delay = delay;
}

int plants::GetDelay()
{
	return delay;
}

void plants::SetY(int y)
{
	this->y = y;
}

void plants::SetCost(int cost)
{
	this->cost = cost;
}

int plants::GetCost()
{
	return cost;
}

int plants:: GetX()
{
	return x;
}

int plants::GetY()
{
	return y;
}

string plants::GetName()
{
	return name;
}

int plants::Getlife()
{
	return life;
}

string plants::GetForma()
{
	return forma;
}

void plants::SetForma(string forma)
{
	this->forma = forma;
}

void plants::SetName(string name)
{
	this->name = name;
}

void plants::SetLife(int life)
{
	this->life = life;
}

plants::~plants()
{
}

ShotPlants::ShotPlants()
{
	SetX(0);
	SetY(0);
	SetForma("|~~|  __");
	SetName("p1");
	SetLife(100);
	SetCost(100);
	SetPrint(true);
	StarTimp();
	//pro.SetDemage(25);
	//pro.SetForma("*");
}

ShotPlants::~ShotPlants()
{
}

void ShotPlants::SetProiectil()
{
	Proiectil p1;
	p1.SetDemage(25);
	p1.SetForma('*');
	p1.SetX(GetX()+4);
	p1.SetY(GetY());
	pro.push_back(p1);
	SetPrint(true);

}

Proiectil ShotPlants::GetProiectil(int k)
{
	return pro[k];
}

void ShotPlants::ErasePro(int k)
{
	pro.erase(pro.begin()+ k);
}

int ShotPlants::GetSizePro()
{
	return pro.size();
}

void ShotPlants::SetProX(int k, int x1)
{
	pro[k].SetX(x1);
}

int ShotPlants::GetProX(int k)
{
	return pro[k].GetX();
}

void ShotPlants::SetProY(int k, int y1)
{
	pro[k].SetY(y1);
}

int ShotPlants::GetProY(int k)
{
	return pro[k].GetY();
}

 char  ShotPlants::GetFormaPro(int k)
{
	return pro[k].GetForma();
}

 void ShotPlants::SetDemagePro(int demage, int k)
 {
	 pro[k].SetDemage(demage);
 }

 int ShotPlants::GetDemage(int k)
 {
	 return pro[k].GetDemage();
 }


SunFlower::SunFlower()
{
	SetX(0);
	SetY(0);
	SetForma(" O O O | ");
	SetName("psun");
	SetLife(50);
	SetCost(50);
	SetPrint(true);
	StarTimp();

}

SunFlower::~SunFlower()
{
}

PotatoPlants::PotatoPlants()
{
	SetX(0);
	SetY(0);
	SetForma("OOOOOOOOO");
	SetName("potato");
	SetLife(250);
	SetCost(50);
	SetPrint(true);
	StarTimp();

}

PotatoPlants::~PotatoPlants()
{
}


DoubleShootPlants::DoubleShootPlants()
{
	SetX(0);
	SetY(0);
	SetForma("|~~|~~  |   OO______");
	SetName("p4");
	SetLife(100);
	SetPrint(true);
	SetCost(150);
	StarTimp();

}

DoubleShootPlants::~DoubleShootPlants()
{
}

void DoubleShootPlants::SetProiectil()
{
	Proiectil p1;
	p1.SetDemage(50);
	p1.SetForma('O');
	p1.SetX(GetX()+7);
	p1.SetY(GetY());
	pro.push_back(p1);
	SetPrint(true);

}

Proiectil DoubleShootPlants::GetProiectil(int k)
{
	return pro[k];
}

void DoubleShootPlants::ErasePro(int k)
{
	pro.erase(pro.begin() + k);
}

int DoubleShootPlants::GetSizePro()
{
	return pro.size();
}

void DoubleShootPlants::SetProX(int k, int x1)
{
	pro[k].SetX(x1);
}

int DoubleShootPlants::GetProX(int k)
{
	return pro[k].GetX();
}

void DoubleShootPlants::SetProY(int k,int y1)
{
	pro[k].SetY(y1);
}

int DoubleShootPlants::GetProY(int k)
{
	return pro[k].GetY();
}

 char  DoubleShootPlants::GetFormaPro(int k)
{
	return pro[k].GetForma();
}

 void DoubleShootPlants::SetDemagePro(int demage, int k)
 {
	 pro[k].SetDemage(demage);
 }

 int DoubleShootPlants::GetDemage(int k)
 {
	 return pro[k].GetDemage();
 }


BombPlants::BombPlants()
{
	SetX(0);
	SetY(0);
	SetForma(" | OOOOOO");
	SetName("pbomb");
	SetLife(100);
	SetCost(25);
	SetPrint(true);
	StarTimp();

}

BombPlants::~BombPlants()
{
}
