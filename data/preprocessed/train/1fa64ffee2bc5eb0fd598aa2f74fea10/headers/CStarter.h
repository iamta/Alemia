#pragma once
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include "CExceptii.h"
#include "CPlayer.h"
using namespace UserInterface;
class CStarter
{
private:
	string DataBase;
	ConsoleInput* conIn;
	ConsoleOutput* conOut;
	void VerifyButton();
	void Login();
	void Register();
	bool VerifyExistence(string Name,string Password);
	CPlayer* Player;
public:
	CPlayer* GetPLayer()const { return Player; };
	CStarter(string DataBase);
	~CStarter() { ; };
};