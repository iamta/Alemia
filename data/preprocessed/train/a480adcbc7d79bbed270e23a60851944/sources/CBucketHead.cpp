#include "CBucketHead.h"
#include "CUtils.h"
void CBucketHead::Draw()
{
	char Plant[5][5] = { {' ','|','-','|',' ' },
						{' ','|',' _','|',' ' },
						{' ',' ','|',' ',' ' },
						{' ','/','|','\\',' ' },
						{' ','/',' ','\\',' ' }
	};
	CUtils::Draw(Point, Plant, conOut);
}

CBucketHead::CBucketHead(CPoint P):CAEntity(P)
{
	Reward = 75;
	Cost = 0;
	Demage = 30;
	Speed = 10;
	this->Draw();
}

CBucketHead::~CBucketHead()
{
	CUtils::ClearMatrix(Point, conOut);
}
