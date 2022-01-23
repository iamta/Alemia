#pragma once
#include <chrono>
#include <time.h>
#include "IResursa.h"
#include "ConsoleOutput.h"
using namespace std::chrono;
using namespace UserInterface;
class CSun:public IResursa
{
private:
	int SunLife;
	CPoint Point;
	ConsoleOutput* conOut;
	std::chrono::time_point<std::chrono::steady_clock>begin;
public:
	bool Verify(CPoint P);
	CSun(CPoint);
	bool RemoveTime();
	virtual ~CSun();
};

