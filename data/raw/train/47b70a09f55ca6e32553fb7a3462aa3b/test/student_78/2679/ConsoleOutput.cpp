#include <windows.h>

#include "ConsoleOutput.h"

using namespace UserInterface;

ConsoleOutput* ConsoleOutput::pInstance = NULL;

ConsoleOutput::ConsoleOutput()
{
	// setting console width and height
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, CON_WIDTH, CON_HEIGHT, TRUE);

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
}

ConsoleOutput& ConsoleOutput::getInstance(int row, int col) {
	return getInstance()(row, col);
}
ConsoleOutput & ConsoleOutput::getInstance()
{
	if(pInstance==NULL)
		pInstance = new ConsoleOutput();

	return *pInstance;
}

ConsoleOutput & UserInterface::ConsoleOutput::operator()(int row, int col)
{
	/*should check wether the row and the column values ar within the limits of the current window*/
	COORD coord;
	coord.X = row;
	coord.Y = col;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return *this;
}
