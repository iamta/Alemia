#pragma once
#define CON_WIDTH 1280
#define CON_HEIGHT 800
#include <iostream>

namespace UserInterface {
	class ConsoleOutput
	{
	private:
		static ConsoleOutput* instance;
		ConsoleOutput();
		~ConsoleOutput();
	public:

		static void RemoveInstance();
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


