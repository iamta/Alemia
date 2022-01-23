#include "Meniu.h"

Meniu::Meniu()
{
	start_button = "START";
	exit_button = "EXIT";
	option_button = "OPTIONS";
	change_name_button = "CHANGE_NAME:";
	classament_button = "CLASAMENT";
}

string Meniu::GetStart()
{
	return start_button;
}

string Meniu::GetExit()
{
	return exit_button;
}

string Meniu::GetOption()
{
	return option_button;
}

string Meniu::GetClasament()
{
	return classament_button;
}

string Meniu::GetChangeName()
{
	return change_name_button;
}


Meniu::~Meniu()
{
}
