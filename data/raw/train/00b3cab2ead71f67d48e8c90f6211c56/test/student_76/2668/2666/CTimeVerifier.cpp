#include "CTimeVerifier.h"
std::chrono::time_point<std::chrono::steady_clock> CTimeVerifier::begin = steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> CTimeVerifier::beginSF = steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> CTimeVerifier::beginPeash = steady_clock::now();
std::chrono::time_point<std::chrono::steady_clock> CTimeVerifier::beginZombie = steady_clock::now();
CTimeVerifier* CTimeVerifier::instance = nullptr;
CTimeVerifier::CTimeVerifier()
{
	begin = steady_clock::now();
	SunDelay = 8;
	SFDelay = 10;
	PeasSh = 15;
	ZombieT = 9;
}

CTimeVerifier& CTimeVerifier::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CTimeVerifier();
		beginSF = steady_clock::now();
	}
	return *instance;
}

bool CTimeVerifier::Sun()
{
	auto end = steady_clock::now();
	if (duration_cast<seconds>(end - begin).count() >= SunDelay)
	{
		begin = end;
		return true;
	}
	return false;
}

bool CTimeVerifier::Zombie()
{
	auto end = steady_clock::now();
	if (duration_cast<seconds>(end - beginZombie).count() >= ZombieT)
	{
		beginZombie = end;
		return true;
	}
	return false;
}

void CTimeVerifier::SunSpeed(int speed)
{
	if (SunDelay >= 2 && speed < 0)
		SunDelay += speed;
	else
		SunDelay += speed;
}

bool CTimeVerifier::SunFlower(bool reset)
{

	auto end = steady_clock::now();
	if (reset == false) {
		if (duration_cast<seconds>(end - beginSF).count() >= SFDelay)
		{
			beginSF = end;
			return true;
		}
	}else beginSF = end;
	return false;
}

bool CTimeVerifier::Peashooter(bool reset)
{
	auto end = steady_clock::now();
	if (reset == false)
	{
		if (duration_cast<seconds>(end - beginPeash).count() >= PeasSh)
		{
			beginPeash = end;
			return true;
		}
	}else beginPeash = end;
	return false;
}
