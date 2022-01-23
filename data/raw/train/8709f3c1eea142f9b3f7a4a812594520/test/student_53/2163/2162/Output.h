#pragma once
#include <iostream>
#include <windows.h>
#define CON_WIDTH 1280
#define CON_HEIGHT 766
using namespace std;
class Output
{
	// setting console width and height
public:
	Output();
	Output & operator() (int row, int col);
	template <typename T>
	friend Output &operator<< (Output &out, T obj)
	{
		std::cout << obj;
		return out;
	}
	virtual~Output();
};

