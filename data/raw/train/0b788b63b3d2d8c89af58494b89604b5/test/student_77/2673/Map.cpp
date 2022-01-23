#include "Map.h"

#include <fstream>
#include <iostream>
#include <string>

void Map::doLVL1()
{
	std::ifstream f("LVL1.txt");

	std::string line;

	while (f)
	{
		std::getline(f, line);
		std::cout << line << std::endl;
	}

	f.close();
}

void Map::doLVL2()
{
	std::ifstream f("LVL2.txt");

	std::string line;

	while (f)
	{
		std::getline(f, line);
		std::cout << line << std::endl;
	}

	f.close();
}

void Map::doLVL3()
{
	std::ifstream f("LVL3.txt");

	std::string line;

	while (f)
	{
		std::getline(f, line);
		std::cout << line << std::endl;
	}

	f.close();
}

void Map::doWin()
{
	std::ifstream f("win.txt");

	std::string line;

	while (f)
	{
		std::getline(f, line);
		std::cout << line << std::endl;
	}

	f.close();
}

void Map::doLose()
{
	std::ifstream f("lose.txt");

	std::string line;

	while (f)
	{
		std::getline(f, line);
		std::cout << line << std::endl;
	}

	f.close();
}
