#include "CGarden.h"
#include "CSun.h"
CGarden* CGarden::instance = nullptr;

void CGarden::Draw()
{
	for(int k=1;k<Col;k++)
	for (int i = 1; i <= 7*Lines; i++)
	{
		if (i % 7 == 0 || i % 7 == 1)
		{

			for (int j = 7*(k-1)+1; j <= 7*k; j++)
			{
				if (j == 7 * (k - 1) + 1 || j == 7 * k)
				{
					(*conOut)(i, j) << " ";
					if (j == 7 * (k - 1) + 1 && i==1 && k!=1)
					{
						CPoint* p = new CPoint(i + 1, j + 1);
						SunPosiblePositions.push_back(p);
						continue;
					}
					if (j == 7 * (k - 1) + 1 && i != 1 && k != 1 && i % 7 == 1)
					{
						CPoint* p = new CPoint(i + 1, j + 1);
						GroundPositions.push_back(p);
					}
				}
				else
					(*conOut)(i, j) << "_";
				if (i % 7 == 0)
				{
					(*conOut)(i, 7 * (k - 1) + 1) << "|";
					(*conOut)(i, 7 * k) << "|";					
				}

			}
		}
		else {
			(*conOut)(i, 7 * (k - 1) + 1) << "|";
			(*conOut)(i, 7 * k) << "|";
		}
	}
}

std::vector<CPoint*> CGarden::GetZombieStartPos()
{
	std::vector<CPoint*>Points;
	for (int i = 1; i < Lines; i++)
	{
		CPoint* P = new CPoint(7*i+2,6*Col+5);
		Points.push_back(P);
	}
	return Points;
}

CGarden& CGarden::GetInstance(CPlayer* PLayer)
{	
	if (instance == nullptr)
	{
		instance = new CGarden();
		instance->conIn = &ConsoleInput::getInstance();
		instance->conOut =&ConsoleOutput::getInstance();
		instance->Player = PLayer;
		instance->Draw();
		instance->TimeVer = nullptr;
	}
	return *instance;
}

void CGarden::RemoveInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void CGarden::SpamSuns()
{
	if (TimeVer == nullptr)
	{
		instance->TimeVer = &CTimeVerifier::GetInstance();
	}
	int random;
	for (auto it = Suns.begin(); it != Suns.end(); it++)
	{
		if ((*it)->RemoveTime() == true)
		{
			delete (*it);
			Suns.erase(it);
			break;
		}
	}
	if (TimeVer->Sun() == true)
	{
		random = rand() % SunPosiblePositions.size();		
		CPoint* ToPrint = SunPosiblePositions[random];
		CSun* Sun = new CSun(*ToPrint);
		Suns.push_back(Sun);
	}
}

bool CGarden::VerifiSun(CPoint P)
{
	for (auto it=Suns.begin(); it < Suns.end(); it++)
	{
		if ((*it)->Verify(P)==true)
		{
			Player->Add_Sun();
			delete (*it);
			Suns.erase(it);			
			return true;
		}
	}
	return false;
}
