#pragma once
#include "PlantsMonitor.h"

class ZombieMonitor
{
private:
	std::map<CPoint*, bool>StartPoints;
	std::vector<IEntity*>Entities;
	int ZombieNumber;
	int MaxZombieNumber;
	ConsoleOutput* conOut;
	CTimeVerifier* TimeVer;
	int WaveTime;
	static std::chrono::time_point<std::chrono::steady_clock>begin;
public:
	void MoveZombie();
	int GenZombie();
	ZombieMonitor(int MaxNumber, std::vector<CPoint*> Points,int WaveTime);
	~ZombieMonitor() { ; };
};

