#pragma once
#include "CAEntity.h"
#include <chrono>
#include <time.h>
#include <vector>
using namespace chrono;

class CPeashooter:public CAEntity
{
private:
	int ShootRate;
	std::chrono::time_point<std::chrono::steady_clock>begin;
	std::chrono::time_point<std::chrono::steady_clock>beginBulletMove;
	std::vector<CPoint*>Peas;
public:
	void Draw();
	bool Shoot();
	CPeashooter(CPoint p);
	~CPeashooter();
};

