#include "PlayGame.h"
#include <conio.h> 

int main()
{
	
	PlayGame& game = PlayGame::getInstance();
	
	game.getAction();

	PlayGame::destroyInstance();

	_getch();
	return 0;
}

