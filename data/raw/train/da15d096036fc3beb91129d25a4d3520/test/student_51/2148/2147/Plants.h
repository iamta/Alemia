#pragma once
#include <iostream>
#include "Proiectil.h"
#include <vector>
#include "Time.h"

using namespace std;


class plants
{
private:
	string forma;
	string name;
	timer timp;
	int life;
	int x;
	int y;
	int cost;
	int delay;
	bool print;
public:
	plants();
	void StarTimp();
	int GetTimp();
	void SetPrint(bool print);
	bool GetPrint();
	void SetX(int x);
	void SetDelay(int delay);
	int GetDelay();
	void SetY(int y);
	void SetCost(int cost);
	int GetCost();
	int GetX();
	int GetY();
	string GetName();
	int Getlife();
	string GetForma();
	void SetForma(string forma);
	void SetName(string name);
	void SetLife(int life);

	~plants();
};


class ShotPlants :public plants
{
private:
	vector<Proiectil> pro;
public:
	ShotPlants();
	~ShotPlants();
	void  SetProiectil();
	Proiectil GetProiectil(int k);
	void ErasePro(int k);
	int GetSizePro();
	void SetProX(int k, int x1);
	int GetProX(int k);
	void SetProY(int k, int y1);
	int GetProY(int k);
	char GetFormaPro(int k);
	void SetDemagePro(int demage, int k);
	int GetDemage(int k);
};

class SunFlower :public plants
{
private:
	char Sun;
	int SupplySun = 25;


public:
	SunFlower();
	~SunFlower();
};

class PotatoPlants :public plants
{
private:

public:
	PotatoPlants();
	~PotatoPlants();
};

class DoubleShootPlants :public plants
{
private:
	vector<Proiectil> pro;

public:
	DoubleShootPlants();
	~DoubleShootPlants();
	void  SetProiectil();
	Proiectil GetProiectil(int k);
	void ErasePro(int k);
	int GetSizePro();
	void SetProX(int k, int x1);
	int GetProX(int k);
	void SetProY(int k,int y1);
	int GetProY(int k);
	char GetFormaPro(int k);
	void SetDemagePro(int demage,int k);
	int GetDemage(int k);
};

class BombPlants : public plants
{
private:

	int PowerDamage = 300;
public:
	BombPlants();
	~BombPlants();

};