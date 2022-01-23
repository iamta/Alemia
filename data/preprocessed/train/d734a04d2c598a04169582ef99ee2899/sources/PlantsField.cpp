#include "PlantsField.h"



PlantsField::PlantsField()
{
}


PlantsField::~PlantsField()
{
}


const void PlantsField::print_field() const
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	for (int i = 10; i <= 35; i++) {
		conOut(i, 18) << char(179);
		conOut(i, 28) << char(179);
		if (i % 5 == 0) {
			for (int j = 18; j <= 28; j++) {
				conOut(i, j) << char(196);
			}
		}
	}

	conOut(14, 19) << "Cost: 100";
	conOut(19, 19) << "Cost: 50";
	conOut(24, 19) << "Cost: 150";
	conOut(29, 19) << "Cost: 50";
	conOut(34, 19) << "Cost: 175";


	SetConsoleTextAttribute(console, FOREGROUND_GREEN);
	
	conOut(12, 19) << "PeaShooter";

	SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED);
	
	conOut(17, 19) << "SunFlower";


	SetConsoleTextAttribute(console, FOREGROUND_RED);
	
	conOut(22, 19) << "CherryBomb";


	SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	
	conOut(27, 19) << "Wall-Nut";


	SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	
	conOut(32, 19) << "IcePea";

}
