#pragma once
#include <iostream>


using namespace std;


class Meniu
{
private:
	string start_button;
	string exit_button;
	string option_button;
	string classament_button;
	string change_name_button;
public:
	Meniu();
	string GetStart();
	string GetExit();
	string GetOption();
	string GetClasament();
	string GetChangeName();

	~Meniu();
};