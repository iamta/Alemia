#define _CRT_SECURE_NO_WARNINGS
#include "Teren.h"
#include <string>
#include <iostream>
#include "Meniu.h"
#include "Coordonate.h"
#include "hPlante.h"//contine headere de la toate plantele

Teren *Teren::ptr = nullptr;

using namespace Plantele;

void Teren::Nivel_1()
{
	std::string linie ="";
		for (int j = 21; j < 236; j++)
		{
			if ((j-20) % 24 == 0)
				linie += "+";
			else
				linie += "_";
		}
	UserInterface::ConsoleOutput::getInstance()(28, 21) << linie;
	UserInterface::ConsoleOutput::getInstance()(40, 21) << linie;
}

void Teren::Nivel_2()
{
	std::string linie_sus_jos = "_";
	for (int i = 21; i < 236; i++)
		linie_sus_jos += "_";
	UserInterface::ConsoleOutput::getInstance()(16, 21) << linie_sus_jos;
	UserInterface::ConsoleOutput::getInstance()(52, 21) << linie_sus_jos;
	for (int j = 44; j < 236; j += 24)
	{
		UserInterface::ConsoleOutput::getInstance()(28, j) << "+";
		UserInterface::ConsoleOutput::getInstance()(40, j) << "+";
	}
}

void Teren::Nivel_3()
{
	for (int i = 4; i <= 64; i += 12)
		for (int j = 44; j <= 236; j += 24)
		{
			UserInterface::ConsoleOutput::getInstance()(i, j) << "+";
			UserInterface::ConsoleOutput::getInstance()(i, j) << "+";
		}
}

Teren::Teren(int lvl)
{
	UserInterface::ConsoleOutput::getInstance()(66, 180) <<"Nume jucator: "<< Meniu::getInstance().get_Nume();
	UserInterface::ConsoleOutput::getInstance()(66, 220) << "Nivel jucat: " << Meniu::getInstance().get_Level();
	UserInterface::ConsoleOutput::getInstance()(1, 0) << "Score: 0";
	UserInterface::ConsoleOutput::getInstance()(3, 0) << "Resurse: 150";
	for(int i=4;i<65;i++)
		UserInterface::ConsoleOutput::getInstance()(i, 0) << "|";
	std::string linie_mica;
	for (int j = 0; j < 20; j++)
		linie_mica += "_";
	for (int i = 4; i < 65; i+=12)
		UserInterface::ConsoleOutput::getInstance()(i, 1) << linie_mica;
	std::string linie_sus_jos="_";
	for (int i = 1; i < 236; i++)
		linie_sus_jos += "_";
	for (int i = 0; i < 65; i++)
		UserInterface::ConsoleOutput::getInstance()(i, 20) << "|";
	UserInterface::ConsoleOutput::getInstance()(4, 0) << linie_sus_jos;//linia de sus
	UserInterface::ConsoleOutput::getInstance()(64, 0) << linie_sus_jos;//linia de jos
	for(int j=44;j<236;j+=24)
		for(int i=0;i<5;i+=2)
			UserInterface::ConsoleOutput::getInstance()(i, j) << "|";

	Floarea_Soarelui flr_sun;
	flr_sun.Draw(flr_sun.get_Coord());
	UserInterface::ConsoleOutput::getInstance()(15, 9) << "\u001b[33m100\u001b[37m";
	Mazare mzr;
	mzr.Draw(mzr.get_Coord());
	UserInterface::ConsoleOutput::getInstance()(27, 9) << "\u001b[32m125\u001b[37m";
	IceBean ice_mzr;
	ice_mzr.Draw(ice_mzr.get_Coord());
	UserInterface::ConsoleOutput::getInstance()(39, 9) << "\u001b[36m175\u001b[37m";
	Cheery cir;
	cir.Draw(cir.get_Coord());
	UserInterface::ConsoleOutput::getInstance()(51, 9) << "\u001b[31m150\u001b[37m";
	Wall_Nut nut;
	nut.Draw(nut.get_Coord());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	UserInterface::ConsoleOutput::getInstance()(63, 9) << "200";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);


	switch (lvl)
	{
	case 1:
		Nivel_1();
		break;
	case 2:
		Nivel_2();
		break;
	case 3:
		Nivel_3();
		break;
	}
}

Teren::Teren()
{
}


Teren::~Teren()
{
	delete ptr;
	ptr = nullptr;
}

void Teren::interactiv_pe_nivele(int row, int col, int lim_1, int lim_2)
{
	for (int j = lim_1; j <= lim_2; j += 12)
		for (int i = 20; i < 236; i += 24)
			if (row >= j && row <= j + 12)
				if (i <= col&&col <= i + 24)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
					UserInterface::ConsoleOutput::getInstance()(j, i) << "+";
					UserInterface::ConsoleOutput::getInstance()(j, i + 24) << "+";
					UserInterface::ConsoleOutput::getInstance()(j + 12, i) << "+";
					UserInterface::ConsoleOutput::getInstance()(j + 12, i + 24) << "+";
					//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					UserInterface::ConsoleOutput::getInstance()(j, i) << "+";
					UserInterface::ConsoleOutput::getInstance()(j, i + 24) << "+";
					UserInterface::ConsoleOutput::getInstance()(j + 12, i) << "+";
					UserInterface::ConsoleOutput::getInstance()(j + 12, i + 24) << "+";
				}

}


void Teren::interactiv(int nivel, std::string action)
{
	int row = 0, col = 0, ok = 0;
	if (action != "") {
		char* poz = _strdup(action.c_str());
		char*tok = strtok(poz, "(");
		if (tok != NULL)
		{
			tok = strtok(NULL, ",");
			if (tok)
				col = atoi(tok);
			tok = strtok(NULL, ")");
			if (tok)
				row = atoi(tok);
			if (row*col)
				ok = 1;
		}

		if (ok)
			for (int i = 4; i < 65; i += 12)
				if (i < row&&row < i + 12)
					if (0 <= col&&col <= 20)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
						UserInterface::ConsoleOutput::getInstance()(i, 0) << "+";
						UserInterface::ConsoleOutput::getInstance()(i, 20) << "+";
						UserInterface::ConsoleOutput::getInstance()(i + 12, 0) << "+";
						UserInterface::ConsoleOutput::getInstance()(i + 12, 20) << "+";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						UserInterface::ConsoleOutput::getInstance()(i, 0) << "+";
						UserInterface::ConsoleOutput::getInstance()(i, 20) << "+";
						UserInterface::ConsoleOutput::getInstance()(i + 12, 0) << "+";
						UserInterface::ConsoleOutput::getInstance()(i + 12, 20) << "+";
					}
		if (ok)
			for (int i = 20; i < 236; i += 24)
				if (row > 0 && row < 4)
					if (col > i&&col < i + 24)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						UserInterface::ConsoleOutput::getInstance()(4, i) << "+";
						UserInterface::ConsoleOutput::getInstance()(4, i + 24) << "+";
						Sleep(200);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						UserInterface::ConsoleOutput::getInstance()(4, i) << "+";
						UserInterface::ConsoleOutput::getInstance()(4, i + 24) << "+";
					}
	}
	
	switch (nivel)
	{
	case 1:
		interactiv_pe_nivele(row, col,28,40);
		break;
	case 2:
		interactiv_pe_nivele(row, col, 16, 52);
		break;
	case 3:
		interactiv_pe_nivele(row, col, 4, 64);
		break;
	}
}

Teren * Teren::getInstance(int a)
{
	if (ptr == nullptr)
		ptr = new Teren(a);
	return ptr;
}
