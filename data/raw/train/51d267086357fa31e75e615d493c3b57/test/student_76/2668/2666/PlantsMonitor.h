#pragma once
#include "IEntity.h"
#include <vector>
#include <map> 
#include "CTimeVerifier.h"
#include "ConsoleOutput.h"
#include "CPlayer.h"
using namespace UserInterface;
class PlantsMonitor
{
private:
	std::map<CPoint*,bool> StartPos;
	std::vector<IEntity*>Entities;
	std::map<CPoint*, bool> GroundPos;
	CTimeVerifier* TimeVer;
	ConsoleOutput* conOut;
	CPoint LastPoint;
	bool SunFlowerD;
	bool PeaShooterD;
public:
	bool VerifyP(CPoint Pt,int Case);
	CPoint* SearchForNewPos(CPoint P);
	void SpawnPlant();
	void MoveP(CPoint P,CPlayer* Player);
	void ShootPlants(std::vector<int>);
	PlantsMonitor(std::vector<CPoint*> Points);
};

