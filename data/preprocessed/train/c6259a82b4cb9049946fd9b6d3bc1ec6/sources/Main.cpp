#include "CGame.h"
#include <conio.h>


int main(void)
{

	CGame player1;
	player1.Log();
	player1.Afisare_Meniu();
	while (true)
	{
		if (player1.Chose() == 1)
			player1.Start();
		if (player1.Chose() == 2)
			player1.afisare_optiuni();
		player1.Afisare_Meniu();
	}
	
	_getch();
 	return 0;
}
