#pragma once
#include<array>
#include<deque>
#include"ConsoleInput.h"
#include"ConsoleOutput.h"
#include"BattleField.h"
class Zombie
{
protected:
	int rezistenta=3;
public:
	Zombie() = default;
	Zombie(int rez) :rezistenta(rez) { ; }
	~Zombie() = default;

	int getRezistenta() { return rezistenta; }
	void setRezistenta() { rezistenta--; }


	void print_Zombie(int, int);
	void delete_zombie(int, int);
	



};

