#pragma once
#define CON_WIDTH 236
#define CON_HEIGHT 66
#include <iostream>

namespace UserInterface {
	class ConsoleOutput
	{
		ConsoleOutput();
		~ConsoleOutput();
		static ConsoleOutput* conOut;
	public:

		void Logo(int, int);

		static ConsoleOutput & getInstance();
		ConsoleOutput & operator() (int row, int col);

		template <typename T>
		friend ConsoleOutput &operator<< (ConsoleOutput &out, T obj)
		{
			std::cout << obj;
			return out;
		}
		friend ConsoleOutput &operator<< (ConsoleOutput &out, wchar_t* obj)
		{
			std::wcout << obj;
			return out;
		}
	};
}


