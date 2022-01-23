#pragma once
#include <iostream>
#include <Windows.h>

class Money
{
	int money;
public:
	Money();
	void print_money();
	void sterge_money();
	int& get_money() { return money; }
	void increase_money() { money += 25; }
	virtual~Money();
};

