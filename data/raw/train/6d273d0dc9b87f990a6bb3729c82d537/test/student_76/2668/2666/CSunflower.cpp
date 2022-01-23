#include "CSunflower.h"
#include "CUtils.h"
void CSunflower::Draw()
{
	char Plant[5][5] = { {' ','*','*','*',' ' },
						{' ','*','*','*',' ' },
						{' ',' ','|',' ',' ' },
						{' ',' ','|',' ',' ' },
						{' ','/',' ','\\',' ' }
	};
	CUtils::Draw(Point, Plant, conOut);
}
CSunflower::CSunflower(CPoint P):CAEntity(P)
{
	Reward = 25;
	Cost = 50;
	Demage = 0;
	Speed = 0;
	this->Draw();
}

CSunflower::~CSunflower()
{
	CUtils::ClearMatrix(Point, conOut);
}
