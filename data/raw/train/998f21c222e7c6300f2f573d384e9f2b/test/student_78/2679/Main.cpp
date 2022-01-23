#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <chrono>
#include <Windows.h>
#include <list>
#include <iostream>

#include "CLog.h"
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include "IDrawable.h"
#include "Sun.h"
#include "Zombie.h"
#include "Joc.h"

#define ROW_TITLE					20			
#define COL_FIRST_STAR_POSITION		75
#define COL_DISTANCE_BETWEEN_STARS	5

using namespace std::chrono;
using std::list;

void doLoadingBar()
{
	static UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	static auto begin = steady_clock::now();
	static int col = COL_FIRST_STAR_POSITION;
	static std::string printedChar = "*";

	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 150)
	{
		begin = end;
		conOut(ROW_TITLE + 1, col) << printedChar;
		if (col >= COL_FIRST_STAR_POSITION + 4 * COL_DISTANCE_BETWEEN_STARS) {
			if (printedChar == "*")
			{
				printedChar = " ";
			}
			else
			{
				printedChar = "*";
			}
			col = COL_FIRST_STAR_POSITION;
		}
		else
		{
			col += COL_DISTANCE_BETWEEN_STARS;
		}
	}
}

int main(void)
{
	CLog& History = CLog::getInstance();

	srand(time(0));
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	UserInterface::ConsoleInput& conIn = UserInterface::ConsoleInput::getInstance();

	Game& game=Game::getInstance();
	game.CreateMap();

	
	while (!game.isOver())
	{
		std::string action = conIn.getUserActions();
		if (action != "")
		{
			conOut(2, 41) << action;
			game.checkSun();
			game.checkPlant();
		}
		game.ZombieAttack();
		game.createSun();
		for (auto p : game.plants) {
			p->update();
		}
		for (auto z : game.zombies) {
			z->update();
		}
		for (auto p : game.projectiles) {
			p->update();
		}
	}
	system("cls");
	

	if (game.isWin())
	{
		UserInterface::ConsoleOutput::getInstance(0, 0) << " You won !\n";
		system("cls");
	}
	else
	{
		UserInterface::ConsoleOutput::getInstance(0, 0) << " Game over\n";
	}


	system("pause");
	return 0;
}

