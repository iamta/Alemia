#include "ConsoleOutput.h"
#include <windows.h>
using namespace UserInterface;

ConsoleOutput *ConsoleOutput::console = nullptr;

ConsoleOutput::ConsoleOutput()
{
	// setting console width and height
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, CON_WIDTH, CON_HEIGHT, TRUE);
	
	system("mode 650");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	

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


ConsoleOutput & ConsoleOutput::getInstance()
{
	if (console == nullptr)
	{
		console = new ConsoleOutput;
	}
	return *console;
}

void UserInterface::ConsoleOutput::destroyInstance()
{
	if (console != nullptr)
	{
		delete(console);
	}
	console = nullptr;
}

void UserInterface::ConsoleOutput::clear()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
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
