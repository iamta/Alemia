#include "Main_menu.h"
#include "IntroOUT.h"
using namespace UserInterface;

void Main_menu::draw()
{
	system("cls");
	IntroOUT &afis = IntroOUT::getInstance();
	afis(15, 75) << "POO versus Zombies ";
	afis(20, 80) << "Main Menu ";
	afis(25, 80) << "1.Create New User";
	afis(30, 80) << "2.Acces existent User";
	afis(35, 80) << "3.Exit game";
}

Main_menu::Main_menu()
{
}


Main_menu::~Main_menu()
{
}
