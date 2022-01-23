#include "Sun.h"

int Sun::ammount = 100;
int Sun::rate = 12;

Sun::Sun(SHORT x, SHORT y)
{
	set_poz({ x, y });
	set();
}

bool Sun::pay(int cost)
{
	if(ammount<cost)
		return false;
	ammount -= cost;
	return true;
}

void Sun::set()
{
	if (box_content()->size() == 0) {
		box_content()->push_back({ "",15 });
		std::string line = " \\ "; line += (char)245; line += " /";
		box_content()->push_back({ line, 14 });
		line = (char)196; line += (char)196; line += " O "; line += (char)196; line += (char)196;
		box_content()->push_back({ line, 14 });
		line = " / "; line += (char)245; line += " \\";
		box_content()->push_back({ line, 14 });
		box_content()->push_back({ "",15 });
	}
}

void Sun::draw()
{
	Output cout = Output::getInstance();
	for (auto i = 0; i < box_content()->size(); i++) {
		COORD p = get_poz();
		cout.consoleUpdate(p.X, p.Y + i , { box_content()->at(i).first, box_content()->at(i).second });
	}
}

void Sun::clear()
{
	box_content()->clear();
}
