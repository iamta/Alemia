#include "CAEntity.h"

bool CAEntity::VerifyPos(CPoint P)
{
	if (P.GetX() == Point.GetX() && P.GetY() == Point.GetY())
		return true;
	return false;
}

CAEntity::CAEntity(CPoint Point)
{
	HP = 100;
	conOut = &ConsoleOutput::getInstance();
	this->Point = Point;
}
