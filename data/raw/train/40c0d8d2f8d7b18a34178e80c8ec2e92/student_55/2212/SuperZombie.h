#pragma once
#include "BucketHeadZombie.h"
#include "PoleVaultingZombie.h"

class SuperZombie: public BucketHeadZombie, public PoleVaultingZombie
{
public:
	SuperZombie() {};
	SuperZombie(int xStart, int yStart, int xSpeed) {
		m_name = "SuperZombie";
		m_health = 200;
		damage = 20;
		this->xStart = xStart;
		this->xSpeed = xSpeed;
		this->yStart = yStart;
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "S";
		SetConsoleTextAttribute(color, 7);
		lastMovement = steady_clock::now();
		movementTime = 350;
		atackTime = 500;
		jumped = 0;
	}
	void print() {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "S";
		SetConsoleTextAttribute(color, 7);
	};

	void freeze() {
		movementTime = 700;
	}
	void move() {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart) << " ";
		yStart -= xSpeed;
		if (yStart % 5 == 0) {
			yStart -= 1;
		}
		if (yStart % 5 == 2) {
			yStart -= 1;
		}
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "S";
		SetConsoleTextAttribute(color, 7);
	};
};

