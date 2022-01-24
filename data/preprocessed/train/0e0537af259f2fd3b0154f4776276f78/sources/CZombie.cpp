#include "CZombie.h"
#include "CUtils.h"
void CZombie::Draw()
{
	char Plant[5][5] = { {' ',' ','O',' ',' ' },
						{' ',' ',' |',' ',' ' },
						{' ','/','|','\\',' ' },
						{' ',' ','|',' ',' ' },
						{' ','/',' ','\\',' ' }
	};
	CUtils::Draw(Point, Plant, conOut);
}
CZombie::CZombie(CPoint P):CAEntity(P)
{
	Reward = 25;
	Cost = 0;
	Demage = 20;
	Speed = 10;
	this->Draw();
}
CZombie::~CZombie()
{
	CUtils::ClearMatrix(Point, conOut);
}
