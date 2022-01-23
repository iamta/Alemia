#pragma once
#include "ConsoleOutput.h"
#include "ConsoleInput.h"

class Teren
{
	void Nivel_1();
	void Nivel_2();
	void Nivel_3();
	Teren(int);
	Teren();
	~Teren();
	static Teren *ptr;
	static void interactiv_pe_nivele(int, int, int, int);
public:
	static void interactiv(int, std::string);
	static Teren* getInstance(int);
};

