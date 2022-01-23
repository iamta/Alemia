#pragma once

#include <iostream>

/*TODO: singleton*/

#define CON_WIDTH 1280
#define CON_HEIGHT 720

namespace UserInterface {
	class ConsoleOutput
	{
	private :

		static ConsoleOutput* pInstance;
		ConsoleOutput();

	public:

		~ConsoleOutput();
		static ConsoleOutput & getInstance();
		static ConsoleOutput & getInstance(int,int);
		ConsoleOutput & operator() (int row, int col);

		template <typename T>
		friend ConsoleOutput &operator<< (ConsoleOutput &out, T obj)
		{
			std::cout << obj;
			return out;
		}
	};
}


