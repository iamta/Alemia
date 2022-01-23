#include "Game.h"
#include<conio.h>


int main(void)
{
	Game&joc = Game::getInstance();
	joc.play();
	
	/*conOut(ROW_TITLE, COL_FIRST_STAR_POSITION) << "Loading cool game now...";*/
	/*while (true)
	{
		doLoadingBar();
		std::string action = conIn.getUserActions();
		if (action != "")
		{
			conOut(41, 2) << action;
		}
	}*/
	
	joc.destroyInstance();
	_getch();
	return 0;
}

