#include "ConsoleOutput.h"
#include <windows.h>
using namespace UserInterface;
ConsoleOutput* ConsoleOutput::instance = nullptr;

ConsoleOutput::ConsoleOutput()
{
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, CON_WIDTH, CON_HEIGHT, TRUE);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &cursorInfo);
}

ConsoleOutput::~ConsoleOutput()
{
}

void UserInterface::ConsoleOutput::RemoveInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

ConsoleOutput& ConsoleOutput::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ConsoleOutput();
	}
	return *instance;
}

ConsoleOutput& UserInterface::ConsoleOutput::operator()(int row, int col)
{
	if (row >= 0 && row <= CON_HEIGHT && col >= 0 && col <= CON_WIDTH)
	{
		COORD coord;
		coord.X = col;
		coord.Y = row;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	return *this;
}
