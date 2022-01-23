#pragma once
#include <iostream>
#include "Time.h"

using namespace std;


class Zombie
{
private:
	int x;
	int y;
	string name;
	int heal;
	int demage;
	string forma;
	timer timp;
	bool move;
public:
	Zombie(int heal, int demage, string forma);
	~Zombie();
	bool GetMove();
	void SetMove(bool move);
	int GetTimp();
	void SetX(int x);
	void SetY(int y);
	void SetName(string name);
	void SetHeal(int heal);
	void SetDemage(int demage);
	void SetForma(string forma);
	int GetX();
	int GetY();
	string GetName();
	int GetHeal();
	int GetDemage();
	string GetForma();


};