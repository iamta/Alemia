#pragma once
#include "Projectile.h"
#include "IZombie.h"

class Zombie:public IZombie
{
protected:
	string m_name;
	int m_health;
	int damage;
	int xStart;
	int yStart;
	int xSpeed;
	steady_clock::time_point lastMovement;
	int movementTime;
	steady_clock::time_point lastAtack;
	int atackTime;
	int jumped;
public:
	Zombie() {};
	Zombie(int xStart, int yStart, int xSpeed) {
		m_name = "Zombie";
		m_health = 100;
		damage = 20;
		this->xStart = xStart;
		this->xSpeed = xSpeed;
		this->yStart = yStart;
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "Z";
		SetConsoleTextAttribute(color, 7);
		lastMovement = steady_clock::now();
		movementTime = 500;
		atackTime = 500;
		jumped = 0;
	}
	int jump() { return jumped; }
	void makeJump() { jumped = 1; }
	virtual void print(){
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart);
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 2);
		cout << "Z";
		SetConsoleTextAttribute(color, 7);
	}
	string name() { return m_name; }
	virtual void freeze() { movementTime = 1000; }
	bool testTime() {
		auto shotTime = steady_clock::now();
		if (duration_cast<milliseconds>(shotTime - lastMovement).count() > movementTime)
		{
			lastMovement = shotTime;
			return true;
		}
		return false;
	}

	int dealDamage() { 
		auto endAtack = steady_clock::now();
		if (duration_cast<milliseconds>(endAtack - lastAtack).count() > atackTime)
		{
			lastAtack = endAtack;
			return damage;
		}
		return 0; 
	}
	void getDamage(int dmg) { m_health -= dmg; }
	virtual void move() {
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
		cout << "Z";
		SetConsoleTextAttribute(color, 7);
	}
	int getX() { return xStart; }
	int getY() { return yStart; }
	int health(){ return m_health; }

	virtual ~Zombie() {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(xStart, yStart) << " ";
	}

};

