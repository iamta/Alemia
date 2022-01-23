#include "CSun.h"
#include "CUtils.h"
bool CSun::Verify(CPoint P)
{
	if (P.GetX() >= this->Point.GetX() && P.GetX() <= this->Point.GetX() + 4 && P.GetY() >= this->Point.GetY() && P.GetY() <= this->Point.GetY() + 4)
	{
		return true;
	}
	return false;
}

CSun::CSun(CPoint point)
{
	char Soare[5][5] = { {' ',' ','*',' ',' ' },
						{' ','*','*','*',' ' },
						{'*','*','*','*','*' },
						{' ','*','*','*',' ' },
						{' ',' ','*',' ',' ' }
	};
	begin = steady_clock::now();
	this->Point = point;
	SunLife = 4;
	conOut = &ConsoleOutput::getInstance();
	CUtils::Draw(point, Soare, conOut);
}

bool CSun::RemoveTime()
{
	auto end = steady_clock::now();
	if (duration_cast<seconds>(end - begin).count() >= SunLife)
	{
		return true;
	}
	return false;
}

CSun::~CSun()
{
	CUtils::ClearMatrix(Point, conOut);
}
