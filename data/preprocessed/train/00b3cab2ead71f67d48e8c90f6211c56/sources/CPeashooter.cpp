#include "CPeashooter.h"
#include "CUtils.h"
void CPeashooter::Draw()
{
	char PS[5][5] = { {' ','|','-','\\',' ' },
						{' ','|','-','/',' ' },
						{' ',' ','|',' ',' ' },
						{' ',' ','|',' ',' ' },
						{' ','/',' ','\\',' ' }
	};
	begin = steady_clock::now();
	CUtils::Draw(Point, PS, conOut);
}
bool CPeashooter::Shoot()
{
	auto end = steady_clock::now();
	if (duration_cast<seconds>(end - begin).count() >= ShootRate)
	{
		begin = steady_clock::now();
		CPoint* P = new CPoint(Point.GetX() + 2, Point.GetY() + 5);
		Peas.push_back(P);
	}
	if (duration_cast<seconds>(end - beginBulletMove).count() >= 1)
	{
		beginBulletMove = steady_clock::now();
		for (auto it = Peas.begin(); it < Peas.end(); it++)
		{
			if (((*it)->GetY() - 1) % 7 == 0 || (*it)->GetY() % 7 == 0)
				(*conOut)((*it)->GetX(), (*it)->GetY()) <<"|";
			else
				(*conOut)((*it)->GetX(), (*it)->GetY()) <<" ";

			(*it)->SetY((*it)->GetY() + 1);
			(*conOut)((*it)->GetX(), (*it)->GetY()) << "o";
		}
		auto it = Peas.begin();
		if (Peas.size() != 0)
		{
			if ((*it)->GetY() == 64)
			{
				(*conOut)((*it)->GetX(), (*it)->GetY()) << " ";
				Peas.erase(it);
			}
		}
	}
	return true;
}
CPeashooter::CPeashooter(CPoint P):CAEntity(P)
{
	beginBulletMove = steady_clock::now();
	Reward = 40;
	ShootRate = 8;
	Cost = 125;
	Demage =15;
	Speed = 0;
	Draw();
}

CPeashooter::~CPeashooter()
{
}
