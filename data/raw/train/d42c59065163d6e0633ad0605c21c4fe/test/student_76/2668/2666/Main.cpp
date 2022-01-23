#include "CMainGame.h"


int main()
{
	CMainGame* Start = &CMainGame::GetInstance("DataBase.txt");
	Start->StartGame();
	return 1;
}