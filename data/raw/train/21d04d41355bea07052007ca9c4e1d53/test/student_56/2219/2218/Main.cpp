#include "UserAction.h"
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include "IntroOUT.h"
#include "IntroJoc.h"
#include <time.h>
#include "Game.h"
#include <thread>
#include <chrono>

#define ROW_TITLE					20			
#define COL_FIRST_STAR_POSITION		75
#define COL_DISTANCE_BETWEEN_STARS	5

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

int main(void)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	UserInterface::ConsoleInput conIn = UserInterface::ConsoleInput::getInstance();

	//IntroJoc joc;
	//joc.LoadingScreen();//astea comentate le-am bagat in player care e apleta de runjoc ;(
	//joc.Runjoc();

	ConsoleGame g("pvz Influencer", 8, 5);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	HWND console_handle = GetConsoleWindow();
	const auto context = GetDC(console_handle);
	while (true)
	{
		
		UserAction action = conIn.getUserActions();
		auto shouldContinue = g.Update(action);
		if (!shouldContinue)
			break;
		std::this_thread::yield();
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	system("pause");
	return 0;
}

