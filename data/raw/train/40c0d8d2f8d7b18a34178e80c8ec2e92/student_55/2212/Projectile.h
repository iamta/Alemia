#pragma once
#include <iostream>
#include "ConsoleOutput.h"
#include <windows.h>
#include <chrono>
#include <time.h>


using namespace std::chrono;
using namespace std;

class Projectile
{
protected:
	static int movementTime;
	int xStart;
	int yStart;
	int xSpeed;
	string m_name;
	steady_clock::time_point lastMovement;
public:
	Projectile() {};
	Projectile(int xStart, int yStart, int xSpeed) {
		this->xStart = xStart;
		this->xSpeed = xSpeed;
		this->yStart = yStart;
		m_name = "Pea";
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 10);
		cout << (char)167;
		SetConsoleTextAttribute(color, 7);
		lastMovement = steady_clock::now();
	}
	bool testTime() {
		auto shotTime = steady_clock::now();
		if (duration_cast<milliseconds>(shotTime - lastMovement).count() > movementTime)
		{
			lastMovement = shotTime;
			return true;
		}
		return false;
	}
	string name() { return m_name; }

	virtual void move() {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart) << " ";
		yStart += xSpeed;
		if (yStart % 5 == 0) {
			yStart += 1;
		}
		if (yStart % 5 == 2) {
			yStart += 1;
		}
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 10);
		cout << (char)167;
		SetConsoleTextAttribute(color, 7);
	}
	int getX() { return xStart; }
	int getY() { return yStart; }

	virtual ~Projectile() {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart) << " ";
	}

};

