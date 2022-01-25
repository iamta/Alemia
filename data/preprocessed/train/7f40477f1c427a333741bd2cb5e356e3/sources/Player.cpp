#include "Player.h"
#include "UserAction.h"
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include <time.h>
#include "Game.h"
#include <thread>
#include <chrono>

void Player::start_game()
{
	start_intro();

	int level;
	cout << "Introduceti Levelul dorit  1 - 3 ";
	cin >> level;


	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	UserInterface::ConsoleInput conIn;

	if (level <= 0 || level > 3)
	{
		cout << "Level not supported";
		return;
	}
	int rows = 8, cols;
	if (level == 1)
	{
		cols = 1;
	}
	if (level == 2)
	{
		cols = 3;
	}
	if (level == 3)
	{
		cols = 5;
	}
	ConsoleGame g("pvz Influencer", rows, cols);//tre sa schimb aici
	HWND console_handle = GetConsoleWindow();
	const auto context = GetDC(console_handle);
	while (true)
	{
		
		UserAction action = conIn.getUserActions();
		g.Update(action);
		std::this_thread::yield();
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	system("pause");
}

void Player::start_intro()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	system("cls");

	conOut(30, 75) << "ZombieLand is waiting for you!";

	Sleep(500);

	system("cls");
}

Player::Player()
{
}


Player::~Player()
{
}
