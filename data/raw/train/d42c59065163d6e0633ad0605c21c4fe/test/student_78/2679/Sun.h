#pragma once
#include <iostream>
#include<time.h>
#include <chrono>
#include "ConsoleInput.h"
#include"ConsoleOutput.h"
#include "Resource.h"
#include "IDrawable.h"
using namespace std::chrono;
class Sun :
	public Resource, public IDrawable
{
private:

	int x;
	int y = int(3);
	static int SunCounter;

public:
	static void addSun(int);
	static int getSunCounter();
	Sun(int a);

	int getX() { return x; }
	int getY() { return y; }

	static Sun* SunFactory();

	void draw() override;
	void update() override;

	~Sun();
};

