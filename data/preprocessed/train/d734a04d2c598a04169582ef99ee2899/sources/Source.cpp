#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <windows.h>
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include "Player.h"
#include "Field.h"
#include "SunField.h"
#include "PlantsField.h"
#include "BattleField.h"
#include "Click.h"
#include"ExceptionHandler.h"
#include"Zombie.h"
#include"Proiectil.h"

#define ROW_TITLE					20			
#define COL_FIRST_STAR_POSITION		75
#define COL_DISTANCE_BETWEEN_STARS	5
#define ROW_NEW_GAME				20		
#define COL_NEW_GAME				77


using namespace std::chrono;

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

void print_new_game() {
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	conOut(ROW_NEW_GAME - 2, COL_NEW_GAME) << "__________";
	for (int i = ROW_NEW_GAME - 1; i < ROW_NEW_GAME + 2; i++) {
		conOut(i, COL_NEW_GAME - 1) << char(179);
	}
	for (int i = ROW_NEW_GAME - 1; i < ROW_NEW_GAME + 2; i++) {
		conOut(i, COL_NEW_GAME + 10) << char(179);
	}
	conOut(ROW_NEW_GAME + 1, COL_NEW_GAME) << "__________";
	conOut(ROW_NEW_GAME, COL_NEW_GAME) << " NEW GAME";
}

bool click(int x, int y) {

	if (x >= 18 && x <= 22 && y >= 76 && y <= 88) {
	label:
		system("CLS");
		UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
		UserInterface::ConsoleInput conIn = UserInterface::ConsoleInput::getInstance();
		conOut(16, 77) << "Name: ";
		std::string username = "";
		std::string action = "";
		
		while (action != "exit") {
			action = conIn.getUserActions();
			if (action.find("Mouse") == std::string::npos)
			{
				if (action != "exit") {
					conOut(16, 82) << action;
					std::string aux;							//last character of user action
					if (action != "")
						aux = action.back();
					username += aux;
				}
			}
		}
		conOut(17, 77) << "Password: ";
		std::string password = "";
		action = "";

		while (action != "exit") {
			action = conIn.getUserActions();
			if (action.find("Mouse") == std::string::npos)
			{
				if (action != "exit") {
					conOut(17, 86) << action;
					std::string aux;						
					if (action != "")
						aux = action.back();
					password += aux;
				}
			}
		}
		Player player(username, password);


		if (player.isOk() == false) {
			goto label;
		}
		return true;
	}
	else {
		ExceptionHandler e("Click in restricted area");
	}
	return false;
}

void load_game() {
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	conOut(ROW_TITLE, COL_FIRST_STAR_POSITION) << "Loading cool game now...";
	while (duration_cast<seconds>(end - begin).count() < 3)
	{
		doLoadingBar();
		end = steady_clock::now();
	}
	system("CLS");
	print_new_game();

	while (true) {
		UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
		UserInterface::ConsoleInput conIn = UserInterface::ConsoleInput::getInstance();
		std::string action = conIn.getUserActions();
		if (action.find("mouse", 0) != std::string::npos)
		{
			conOut(41, 2) << action;
			if (action.find("click", 0) != std::string::npos)
				if (click(conIn.get_y(), conIn.get_x()) == true)
					break;
		}
	}
	system("CLS");

	SunField* sf; 
	sf = sf->GetInstance(); 
	sf->print_field();
	BattleField* bf; 
	bf = bf->GetInstance(); 
	bf->print_field();
	PlantsField pf; pf.print_field();
	Click click;

	Zombie* zombie = new Zombie(5);
	int zombie_poz = rand() % 5 + 1;
	int i = 90;
	Proiectil* proiectil = new Proiectil(3);
	int proiectil_pos = 2;
	int j = 42;
	int rez = 3;
	int putSun = 2;
	while (true) {
		UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
		UserInterface::ConsoleInput conIn;
		clock_t t;
		t = clock();
		while (clock() - t < 4000)
		{
			srand(time(NULL));
			int sun_poz = rand() % 8 + 1;
			sf->print_sun(sun_poz);
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

			std::string action = conIn.getUserActions();
			if (action.find("Mouse", 0) != std::string::npos) {
				conOut(41, 2) << action;
				if (action.find("click", 0) != std::string::npos)
					click.get_click(conIn.get_y(), conIn.get_x());
			}
			
			if (rez >= 0)
				{
					zombie->print_Zombie(zombie_poz, i);
					
				}
			if (putSun < 0)
			{
				proiectil->throwProiectil(proiectil_pos, j);
			}
			else
			{
				putSun--;
			}
		}
		
		zombie->delete_zombie(zombie_poz, i);
		proiectil->deleteProiectil(proiectil_pos, j);
		i -= 7;
		j += 7;
		rez = rez--;
	}
}



int main() {

	load_game();

	
}
