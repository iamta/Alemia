#include "CPlayer.h"

CPlayer::CPlayer(string Name, string Password):Name(Name),Password(Password)
{
	Points = 0;
	SunPoints = 0;
	round = 1;
}

void CPlayer::Add_Sun()
{
	SunPoints += 50;
	Points += 10;
}

void CPlayer::Add_Points(int NumberOfPoints)
{
	Points += NumberOfPoints;
}

void CPlayer::Finish(bool State)
{
	State = false;
	string Mesaj = "Player-ul a";
	if (State == true)
		Mesaj += " castigat";
	else Mesaj += " pierdut";
	Mesaj += " cu " + to_string(Points) + " puncte in runda " + to_string(round);
	LogsMonitor::SaveLog(Mesaj);
}
