#pragma once
#include "IEntity.h"
#include "ConsoleOutput.h"
using namespace UserInterface;

class CAEntity:public IEntity
{
protected:
	int Cost;
	int HP;
	int Demage;
	int Speed;
	int Reward;
	CPoint Point;
	ConsoleOutput* conOut;
public:
	CPoint GetPoint()const { return Point; }
	int GetCost() { return Cost; }
	bool VerifyPos(CPoint P);
	void TakeDemage(int Dmg) { HP -= Dmg; };
	int DealDemage() { return Demage; };
	int GetReward() { return Reward; };
	CAEntity(CPoint Point);
	void SetPoint(CPoint p) { this->Point = p; };
};

