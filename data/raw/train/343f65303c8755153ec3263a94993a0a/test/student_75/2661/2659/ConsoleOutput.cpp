#include "ConsoleOutput.h"
#include <windows.h>
using namespace UserInterface;

ConsoleOutput* ConsoleOutput::conOut = nullptr;

ConsoleOutput::ConsoleOutput()
{
	// setting console width and height
	HWND console = GetConsoleWindow();
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	// hiding scrollbar
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	// hide blinking cursor
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(handle, &cursorInfo);
}

ConsoleOutput::~ConsoleOutput()
{
	delete conOut;
	conOut = nullptr;
}

void UserInterface::ConsoleOutput::Logo(int row, int col)
{
	ConsoleOutput conOut;

	conOut(row, col) << "ooooooooo.                oooooooooooo ";
	conOut(row + 1, col) << "`888   `Y88.             d'''''''d888'";
	conOut(row + 2, col) << " 888   .d88' oooo    ooo       .888P";
	conOut(row + 3, col) << " 888ooo88P'   `88.  .8'       d888'";
	conOut(row + 4, col) << " 888           `88..8'      .888P";
	conOut(row + 5, col) << " 888            `888'      d888'    .P";
	conOut(row + 6, col) << "o888o            `8'     .8888888888P";

}

ConsoleOutput & ConsoleOutput::getInstance()
{
	if(conOut==nullptr)
		ConsoleOutput *console = new ConsoleOutput();
	return *conOut;
}

ConsoleOutput & UserInterface::ConsoleOutput::operator()(int row, int col)
{
	/*should check wether the row and the column values ar within the limits of the current window*/
	COORD coord;
	coord.X = col;
	coord.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return *this;
}
