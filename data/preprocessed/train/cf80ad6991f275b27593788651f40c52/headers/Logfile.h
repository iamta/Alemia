#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>

class Logfile
{
	std::string username;
	FILE * f;
public:
	Logfile();
	void enter_username();
	void get_user_action(std::string string);
	void save_exit_userdata();
	virtual~Logfile();
};

