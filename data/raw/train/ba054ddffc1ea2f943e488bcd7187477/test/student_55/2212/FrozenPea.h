#pragma once
#include "Projectile.h"

class FrozenPea:public Projectile
{
public:
	FrozenPea(int xStart, int yStart, int xSpeed) {
		this->xStart = xStart;
		this->xSpeed = xSpeed;
		this->yStart = yStart;
		m_name = "FrozenPea";
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 11);
		cout << (char)233;
		SetConsoleTextAttribute(color, 7);
		lastMovement = steady_clock::now();
	}
	void move() {
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
		SetConsoleTextAttribute(color, 11);
		cout << (char)233;
		SetConsoleTextAttribute(color, 7);
	}
};

