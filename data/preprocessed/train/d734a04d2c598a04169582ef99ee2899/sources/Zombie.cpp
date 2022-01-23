#include "Zombie.h"

void Zombie::print_Zombie(int pos, int i)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (i > 40)
	{
		switch (pos)
		{
		case 1:
			conOut(13, i) << "Zombie";
			break;
		case 2:
			conOut(18, i) << "ZB";
			break;
		case 3:
			conOut(23, i) << "ZB";
			break;
		case 4:
			conOut(28, i) << "Zombie";
			break;
		case 5:
			conOut(33, i) << "Zombie";
			break;
		}
	}
	else
	{
		conOut(8, 40) << "Joc pierdut!";
		return;
	}


}


void Zombie::delete_zombie(int pos, int i)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (pos)
	{
	case 1:
		conOut(13, i) << "      ";
		break;
	case 2:
		conOut(18, i) << "      ";
		break;
	case 3: 
		conOut(23, i) << "      ";
		break;
	case 4:
		conOut(28, i) << "      ";
		break;
	case 5:
		conOut(33, i) << "      ";
		break;
	}
}