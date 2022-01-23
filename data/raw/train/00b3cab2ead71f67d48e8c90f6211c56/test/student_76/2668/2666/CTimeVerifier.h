#pragma once
#include <chrono>
#include <time.h>
using namespace std::chrono;

class CTimeVerifier
{
private:
	int SunDelay;
	int SFDelay;
	int PeasSh;
	int ZombieT;
	static std::chrono::time_point<std::chrono::steady_clock>begin;
	static std::chrono::time_point<std::chrono::steady_clock>beginSF;
	static std::chrono::time_point<std::chrono::steady_clock>beginPeash;
	static std::chrono::time_point<std::chrono::steady_clock>beginZombie;
	CTimeVerifier();
	static CTimeVerifier* instance;
public:
	static CTimeVerifier& GetInstance();	
	bool Sun();
	bool Zombie();
	void SunSpeed(int);
	bool SunFlower(bool reset=false);
	bool Peashooter(bool reset=false);
};

