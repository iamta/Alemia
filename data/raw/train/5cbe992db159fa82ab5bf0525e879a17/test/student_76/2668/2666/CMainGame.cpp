#include "CMainGame.h"
#include "CUtils.h"
CMainGame* CMainGame::instance = nullptr;

void CMainGame::RefreshScore()
{
	(*conOut)(2, 2) << "Suns";	
	(*conOut)(3, 2) << Player->GetResources();
	if (Player->GetResources() < 100)
	(*conOut)(3, 4) << " ";
	(*conOut)(4, 2) << "SCORE";
	(*conOut)(5, 2) << Player->GetPoints();
}

CMainGame& CMainGame::GetInstance(string filename)
{
	if (instance == nullptr)
	{
		instance = new CMainGame();
		instance->conIn = &(ConsoleInput::getInstance());
		instance->conOut = &(ConsoleOutput::getInstance());
		instance->Start = new CStarter(filename);
		instance->Player = instance->Start->GetPLayer();
		instance->Garden = &(CGarden::GetInstance(instance->Player));
		instance->PlantMon = new PlantsMonitor(instance->Garden->GetGroundPosition());
		instance->ZombieMon = new ZombieMonitor(3, instance->Garden->GetZombieStartPos(),40);
	}
	return *instance;	
}

void CMainGame::RemoveInstace()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void CMainGame::StartGame()
{
	CTimeVerifier* ver = &CTimeVerifier::GetInstance();
	bool PlantClicked = false;
	try {
		while (true)
		{
			CPoint Point(0, 0);
			string Action = (*conIn).getUserActions(Point);
			if (Action == "double click")
			{
				if (Garden->VerifiSun(Point) == true)
					continue;
				if (PlantClicked == true)
				{
					PlantMon->MoveP(Point, Player);
					PlantClicked = false;
					continue;
				}
				if (PlantMon->VerifyP(Point, 0) == true)
				{
					PlantClicked = true;
				}
			}
			RefreshScore();
			Garden->SpamSuns();
			this->PlantMon->SpawnPlant();
			int ZombieX=this->ZombieMon->GenZombie();
			if (ZombieX != 0 && std::find(ZombieLines.begin(), ZombieLines.end(), ZombieX) == ZombieLines.end())
				ZombieLines.push_back(ZombieX);
			this->PlantMon->ShootPlants(ZombieLines);
			ZombieMon->MoveZombie();
		}
	}
	catch (CExceptii exc)
	{
		exc.PrintError();
		if (exc.GetCode() == 15)
		{
			Player->Finish(0);
			CUtils::CleanScreen(conOut);
			(*conOut)(15, 10) << "Ai pierdut cu scorul de " <<Player->GetPoints()<<" !";
		}
	}
	catch (exception exc)
	{
		LogsMonitor::SaveError(exc.what());
	
	}
}
