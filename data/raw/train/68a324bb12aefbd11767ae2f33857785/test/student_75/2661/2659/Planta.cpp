#define _CRT_SECURE_NO_WARNINGS
#include "Planta.h"

using namespace Plantele;

Planta::Planta()
{
}


Planta::~Planta()
{

}

void Planta::set_Culoare(const char* cul)
{
	strcpy(culoare, cul);
}

void Planta::Draw(coordonate &where)
{
	if (where.seminte == WALL_NUT)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y + 10) << desen;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
	}
	else
	{
		UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y + 10) << culoare;
		UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y + 10) << desen;
		UserInterface::ConsoleOutput::getInstance()(where.x + 6, where.y + 10) << "\u001b[37m";
	}
}



void Planta::set_Desen(const char*des)
{
	strcpy(desen, des);
}