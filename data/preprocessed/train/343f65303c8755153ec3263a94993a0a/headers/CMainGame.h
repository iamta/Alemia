#pragma once
#include "CStarter.h"
#include "CGarden.h"
#include "ZombieMonitor.h"
class CMainGame
{
private:
	CGarden* Garden;
	CStarter* Start;
	ConsoleInput* conIn;
	ConsoleOutput* conOut;
	PlantsMonitor* PlantMon;
	ZombieMonitor* ZombieMon;
	CMainGame() { ; };
	~CMainGame() { ; };
	static CMainGame* instance;
	CPlayer* Player;
	void RefreshScore();
	std::vector<int>ZombieLines;
public:
	static CMainGame& GetInstance(string filename);
	static void RemoveInstace();
	void StartGame();
};

