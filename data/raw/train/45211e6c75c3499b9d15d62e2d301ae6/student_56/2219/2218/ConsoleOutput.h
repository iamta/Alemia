#pragma once
/*TODO: singleton*/
#define CON_WIDTH 1280
#define CON_HEIGHT 720
#include <windows.h>
#include <iostream>

namespace UserInterface {
	class ConsoleOutput
	{
		static ConsoleOutput* pInstance;
	public:
		ConsoleOutput();
		~ConsoleOutput();

		static ConsoleOutput & getInstance();
		ConsoleOutput & operator() (int row, int col);

		template <typename T>
		friend ConsoleOutput &operator<< (ConsoleOutput &out, T obj)
		{
			std::cout << obj;
			return out;
		}
		static void Refresh()
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
	};
}


