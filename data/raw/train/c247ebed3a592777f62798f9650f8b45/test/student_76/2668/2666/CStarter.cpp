#include "CStarter.h"
#include "CPoint.h"
#include "CUtils.h"
#include "LogsMonitor.h"
#define UserNCol 25
#define UserNLin 15
void CStarter::VerifyButton()
{
	(*conOut)(UserNLin - 2, UserNCol) << "Apasa un buton:";
	(*conOut)(UserNLin, UserNCol) << "Login?";
	(*conOut)(UserNLin + 2, UserNCol) << "Register?";
	CPoint* Point = new CPoint(0,0);

	while (true)
	{
		std::string action = conIn->getUserActions(*Point);
		if (action == "double click" && Point->GetX() != 0)
		{
			if (Point->GetX() == UserNLin && Point->GetY() >= UserNCol && Point->GetY() <= UserNCol + 6)
			{
				Login();
				break;
			}
			if (Point->GetX() == UserNLin+2 && Point->GetY() >= UserNCol && Point->GetY() <= UserNCol + 6)
			{
				Register();
				break;
			}
		}
	}

	
}

void CStarter::Login()
{
	conIn->ResetFlags();
	(*conOut)(UserNLin-2, UserNCol) << "LOG-IN         ";
	string Name = " ", Password = " ";
	(*conOut)(UserNLin, UserNCol) << "UserName: ";
	(*conOut)(UserNLin + 2, UserNCol) << "Password: ";
	do
	{
		(*conOut)(UserNLin, UserNCol + 10);
		std::getline(cin, Name, '\n');
		(*conOut)(UserNLin + 2, UserNCol + 10);
		std::getline(cin, Password, '\n');
	} while (VerifyExistence(Name, Password) == false);
	LogsMonitor::SaveLog("Contul " + Name + " si parola " + Password + " s-a logat!");
	CUtils::CleanScreen(conOut);
	Player = new CPlayer(Name, Password);
	conIn->SetFlags();
}

void CStarter::Register()
{
	conIn->ResetFlags();
	(*conOut)(UserNLin - 2, UserNCol) << "REGISTER        ";
	string Name = " ", Password = " ";
	(*conOut)(UserNLin, UserNCol) << "UserName: ";
	(*conOut)(UserNLin + 2, UserNCol) << "Password: ";
	do {
		(*conOut)(UserNLin, UserNCol + 10);
		std::getline(cin, Name, '\n');
		(*conOut)(UserNLin + 2, UserNCol + 10);
		std::getline(cin, Password, '\n');
		if (Password.length() >= 8 && Name.length() >= 3 && VerifyExistence(Name,"#####")==false)
		{
			ofstream f;
			f.open(DataBase, ios_base::app);
			f << Name << " " << Password << endl;
			f.close();
			LogsMonitor::SaveLog("Contul "+Name + " cu parola " + Password + " creat !");
			break;
		}
		else
		{
			CUtils::CleanLine(new CPoint(UserNLin, UserNCol + 10), conOut, Name.length());
			CUtils::CleanLine(new CPoint(UserNLin + 2, UserNCol + 10), conOut, Password.length());
			(*conOut)(UserNLin + 4, UserNCol + 4) << "WRONG!";
		}
	} while (true);
	CUtils::CleanLine(new CPoint(UserNLin + 4, UserNCol + 4), conOut, 6);
	CUtils::CleanLine(new CPoint(UserNLin, UserNCol + 10), conOut, Name.length());
	CUtils::CleanLine(new CPoint(UserNLin + 2, UserNCol + 10), conOut, Password.length());
	Login();
	conIn->SetFlags();
}

bool CStarter::VerifyExistence(string Name, string Password)
{
	ifstream f;
	f.open(this->DataBase);
	if (f.is_open() == false)
		throw new CExceptii("Baza de date inexistenta", 0);
	while (!f.fail())
	{
		string Line;
		std::getline(f, Line);
		if (Name + " " + Password == Line)
			return true;
		if (Line.find(Name)!=string::npos && Password == "#####")
			return true;
	}
	CUtils::CleanLine(new CPoint(UserNLin, UserNCol + 10),conOut,Name.length());
	CUtils::CleanLine(new CPoint(UserNLin+2, UserNCol + 10), conOut, Password.length());
	(*conOut)(UserNLin + 4, UserNCol + 4) << "WRONG!";
	LogsMonitor::SaveError("Contul " + Name + " si parola " + Password + " a incercat sa se logheze!");
	return false;
}

CStarter::CStarter(string DataBase)
{
	conIn =&ConsoleInput::getInstance();
	conOut =&ConsoleOutput::getInstance();
	conIn->SetFlags();
	this->DataBase = DataBase;
	VerifyButton();
}
