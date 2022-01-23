#pragma once
#include "Zombie.h"

class BucketHeadZombie:virtual public Zombie
{
public:
	BucketHeadZombie() {};
	BucketHeadZombie(int xStart, int yStart, int xSpeed) {
		m_name = "BucketHeadZombie";
		m_health = 200;
		damage = 20;
		this->xStart = xStart;
		this->xSpeed = xSpeed;
		this->yStart = yStart;
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "B";
		SetConsoleTextAttribute(color, 7);
		lastMovement = steady_clock::now();
		movementTime = 500;
		atackTime = 500;
	}

	void print() override {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "B";
		SetConsoleTextAttribute(color, 7);
	}

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
		cout << "B";
		SetConsoleTextAttribute(color, 7);
	}

	~BucketHeadZombie() {};

};

