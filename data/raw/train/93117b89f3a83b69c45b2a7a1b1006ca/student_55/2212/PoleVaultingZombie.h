#pragma once
#include "Zombie.h"

class PoleVaultingZombie:virtual public Zombie
{
public:
	PoleVaultingZombie() {};
	PoleVaultingZombie(int xStart, int yStart, int xSpeed) {
		m_name = "PoleVaultingZombie";
		m_health = 80;
		damage = 20;
		this->xStart = xStart;
		this->xSpeed = xSpeed;
		this->yStart = yStart;
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "P";
		SetConsoleTextAttribute(color, 7);
		lastMovement = steady_clock::now();
		movementTime = 350;
		atackTime = 500;
		jumped = 0;
	}

	void print() override {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "P";
		SetConsoleTextAttribute(color, 7);
	}

	void freeze() { movementTime = 700; }
	virtual void move() override {
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
		cout << "P";
		SetConsoleTextAttribute(color, 7);
	}
};

