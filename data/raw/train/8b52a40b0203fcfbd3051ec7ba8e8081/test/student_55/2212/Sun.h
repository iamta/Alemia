#pragma once
#include <iostream>
#include "ConsoleOutput.h"
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <vector>
#include <iterator>
#include "IDrawable.h"

using namespace std;

class Sun : public IDrawable
{
private:
	int value;
	static int sunSpawnTime;
public:
	Sun() {
		value = 25;
		x = 2;
		srand(time(NULL));
		y = ((rand() % 9) + 1) * 5 + 2;

		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				conOut(x + i, y + j);
				HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(color, 6);
				cout << char(178);
			}
		}
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(color, 7);
	}

	static int getSunSpawnTime() {
		return sunSpawnTime;
	}

	static void reduceSunSpawnTime() {
		sunSpawnTime /= 2;
	}

	static void restoreSunSpawnTime() {
		sunSpawnTime *= 2;
	}

	int getValue() { return value; }

	~Sun() {
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				conOut(x + i, y + j);
				cout << " ";
			}
		}
	}
};

