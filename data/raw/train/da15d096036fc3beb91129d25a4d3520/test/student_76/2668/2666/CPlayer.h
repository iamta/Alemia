#pragma once
#include "CExceptii.h"
class CPlayer
{
private:
	string Name;
	string Password;
	int Points;
	int round;
	int SunPoints;
public:
	CPlayer(string Name, string Password);
	int GetResources() { return SunPoints; };
	void Add_Sun();
	void Add_Points(int NumberOfPoints);
	int GetPoints()const { return Points; }
	void GiveRes(int Res) { SunPoints -= Res; }
	void Finish(bool Case);
};

