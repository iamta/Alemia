#include "Proiectil.h"


void Proiectil::throwProiectil(int pos, int i)
{
	UserInterface::ConsoleInput conIn = UserInterface::ConsoleInput::getInstance();
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	BattleField* bf;
	bf = bf->GetInstance();


	if (bf->get_field_position(conIn.get_y(), conIn.get_x()) == -1) 
	{
		if (i >= 40 && i<=95)
		{
			switch (pos)
			{
			case 1:
				conOut(13, i) << "bomb";
				break;
			case 2:
				conOut(18, i) << "bomb";
				break;
			case 3: 
				conOut(23, i) << "bomb";
				break;
			case 4:
				conOut(28, i) << "bomb";
				break;
			case 5:
				conOut(33, i) << "bomb";
				break;
			}
		}
		else
		{
			return;
		}


	}
}

void Proiectil::deleteProiectil(int pos, int i)
{

	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (pos)
	{
	case 1:
		conOut(13, i) << "     ";
		break;
	case 2:
		conOut(18, i) << "     ";
		break;
	case 3:
		conOut(23, i) << "     ";
		break;
	case 4:
		conOut(28, i) << "     ";
		break;
	case 5:
		conOut(33, i) << "     ";
		break;
	}
}