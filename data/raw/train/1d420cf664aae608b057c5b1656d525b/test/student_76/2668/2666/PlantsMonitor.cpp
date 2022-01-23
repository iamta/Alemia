#include "PlantsMonitor.h"
#include "CSunflower.h"
#include "CPeashooter.h"
#include "CUtils.h"
bool PlantsMonitor::VerifyP(CPoint Pt,int Case)
{
	for (auto it = StartPos.begin(); it != StartPos.end(); it++)
	{
		if (Pt.GetX() >= (*it).first->GetX() && Pt.GetX() <= (*it).first->GetX()+4 && Pt.GetY() >= (*it).first->GetY() && Pt.GetY() <= (*it).first->GetY() + 4)
		{
			if (Case == 0)
			{
				LastPoint = *(*it).first;				
			}
			if (Case == 1)
				(*it).second = false;
			return true;
		}
	}
	return false;
}

CPoint* PlantsMonitor::SearchForNewPos(CPoint Pt)
{
	for (auto it = GroundPos.begin(); it != GroundPos.end(); it++)
	{
		if (Pt.GetX() >= (*it).first->GetX() && Pt.GetX() <= (*it).first->GetX() + 4 && Pt.GetY() >= (*it).first->GetY() && Pt.GetY() <= (*it).first->GetY() + 4 && (*it).second == false)
		{
			(*it).second = true;
			return (*it).first;
		}
	}
	return nullptr;
}

void PlantsMonitor::SpawnPlant()
{
	if (TimeVer == nullptr)
		this->TimeVer = &CTimeVerifier::GetInstance();

	for (auto it = StartPos.begin(); it != StartPos.end(); it++)
	{
		if ((*it).second == false)
		{
			int random = rand() % 2;
			if (random == 1 && SunFlowerD == true)
			{
				if (TimeVer->SunFlower() == true)
				{
					SunFlowerD = false;
					IEntity* Ent = new CSunflower(*(*it).first);
					this->Entities.push_back(Ent);
					(*it).second = true;

				}
			}
			else if (random == 0 && PeaShooterD == true) {
				if (TimeVer->Peashooter() == true)
				{
					PeaShooterD = false;
					IEntity* Ent = new CPeashooter(*(*it).first);
					this->Entities.push_back(Ent);
					(*it).second = true;
				}
			}
			break;
		}
	}
}

void PlantsMonitor::MoveP(CPoint P,CPlayer* Player)
{
	for (int i=0;i<Entities.size();i++)
	{
		CAEntity* Ent = (CAEntity*)Entities[i];
		if (Ent->VerifyPos(LastPoint) == true)
		{
			if (Ent->GetCost() <= Player->GetResources())
			{
				CPoint* Pt = SearchForNewPos(P);
				if (Pt != nullptr)
				{
					CUtils::ClearMatrix(LastPoint, conOut);
					Ent->SetPoint(*Pt);
					Ent->Draw();
					if (Ent->Shoot() == false)
					{
						SunFlowerD = true;
						TimeVer->SunFlower(true);
						TimeVer->SunSpeed(-1);
					}
					else {
						PeaShooterD = true;
						TimeVer->Peashooter(true);
					}
					Player->GiveRes(Ent->GetCost());
					Player->Add_Points(Ent->GetReward());
					VerifyP(LastPoint, 1);
					
				}
				(*conOut)(43, 2) << "             ";
			}
			else { (*conOut)(43, 2) << "No resources"; }
		}
	}
}

void PlantsMonitor::ShootPlants(std::vector<int> Places)
{
	for (int i = 0; i < Entities.size(); i++)
	{	
		CAEntity* Ent = (CAEntity*)Entities[i];
		if (VerifyP(Ent->GetPoint(), 2) == false)
			if (std::find(Places.begin(), Places.end(), Ent->GetPoint().GetX()) != Places.end())
				Entities[i]->Shoot();
		(*conOut)(Ent->GetPoint().GetX() + 2, Ent->GetPoint().GetY() + 2) << '|';
	}
}

PlantsMonitor::PlantsMonitor(std::vector<CPoint*> Points)
{
	int k = 1;
	for (int i = 1; i <= 5; i++)
	{
		CPoint* p = new CPoint(2+(7*k),2);
		k++;
		StartPos[p] = false;
	}
	for (int i = 0; i < Points.size(); i++)
	{
		GroundPos[Points[i]] = false;
	}
	this->conOut = &(ConsoleOutput::getInstance());
	this->TimeVer = nullptr;
	SunFlowerD = true;
	PeaShooterD = true;
}
