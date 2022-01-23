#include "ZombieMonitor.h"
#include "CZombie.h"
#include "CBucketHead.h"
using namespace chrono;
std::chrono::time_point<std::chrono::steady_clock> ZombieMonitor::begin= steady_clock::now();

void ZombieMonitor::MoveZombie()
{
	for (auto it = Entities.begin(); it != Entities.end(); it++)
	{
		CAEntity* Ent = (CAEntity*)(*it);
		if (Ent->GetPoint().GetX() == 1)
			throw new CExceptii("End game", 15);
	}
}

int ZombieMonitor::GenZombie()
{
	if(TimeVer==nullptr)
		TimeVer = &(CTimeVerifier::GetInstance());

	if (ZombieNumber < MaxZombieNumber)
	{
		auto end = steady_clock::now();
		if (duration_cast<seconds>(end - begin).count() >= WaveTime)
		{
			if (TimeVer->Zombie() == true)
			{
				for (auto it = StartPoints.begin(); it != StartPoints.end(); it++)
				{
					if ((*it).second == false)
					{
						(*it).second = true;
						int random = rand() % 2;
						if (random == 1)
						{
							IEntity* Ent = new CBucketHead(*(*it).first);
							Entities.push_back(Ent);
						}
						else {
							IEntity* Ent = new CZombie(*(*it).first);
							Entities.push_back(Ent);
						}
						ZombieNumber++;
						return (*it).first->GetX();
					}
				}
			}
		}
	}
	return 0;
}

ZombieMonitor::ZombieMonitor(int MaxNumber, vector<CPoint*> Points, int WaveTime)
{
	MaxZombieNumber = MaxNumber;
	this->WaveTime = WaveTime;
	for (int i = 0; i < Points.size(); i++)
	{
		StartPoints[Points[i]] = false;
	}
	conOut = &(ConsoleOutput::getInstance());
	TimeVer = nullptr;
	ZombieNumber = 0;
}
