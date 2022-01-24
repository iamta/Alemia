#pragma once
/*TODO: singleton*/
#define CON_WIDTH 1280
#define CON_HEIGHT 720
#include <iostream>

namespace UserInterface {
	class IntroOUT
	{
	public:
		IntroOUT();
		~IntroOUT();

		static IntroOUT & getInstance();
		IntroOUT & operator() (int row, int col);

		template <typename T>
		friend IntroOUT &operator<< (IntroOUT &out, T obj)
		{
			std::cout << obj;
			return out;
		}
	};
}


