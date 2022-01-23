#pragma once
#include "ConsoleOutput.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include "log_Actiuni.h"

class Meniu
{
	std::string nume_utilizator;
	std::string parola;
	int nivel;
	Meniu();
	~Meniu();
	static Meniu*ptr;
	void chenar();
	bool verifica_nume_parola(std::string, std::string);
	
public:
	static Meniu& getInstance();
	void Log();
	const int get_Level();
	const std::string get_Nume();
	void situatie_de_exit(int);
};

