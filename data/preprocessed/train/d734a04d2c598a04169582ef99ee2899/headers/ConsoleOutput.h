#pragma once
#define CON_WIDTH 1280
#define CON_HEIGHT 720
#include <iostream>
#include <windows.h>

namespace UserInterface {
	class ConsoleOutput
	{
	private:
		static ConsoleOutput* instance;
	public:
		ConsoleOutput();
		~ConsoleOutput();
		static ConsoleOutput& getInstance();
		ConsoleOutput& operator() (int row, int col);
		template <typename T>
		friend ConsoleOutput& operator<< (ConsoleOutput& out, T obj)
		{
			std::cout << obj;
			return out;
		}

	};
}
