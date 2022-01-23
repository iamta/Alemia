#include "Logfile.h"



Logfile::Logfile()
{
}

void Logfile::enter_username()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 15,15});
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	
	std::cout << "Please enter your name !\n";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 15,17 });
	getline(std::cin, username);
	username += ".txt";
	f = fopen(username.c_str(), "a");
	if (f == NULL)
	{
		std::cout << "Eroare la deschidere fisier\n";
	}
	get_user_action(username);
	system("cls");
	fclose(f);
}


void Logfile::get_user_action(std::string string)
{
	time_t time_1;
	struct tm*time_info;
	time(&time_1);
	time_info = localtime(&time_1);
	 f = fopen(username.c_str(), "a");
	fputs(string.c_str(), f);
	fprintf(f, "%s", "		");
	fprintf(f, "%s", asctime(time_info));
	fprintf(f, "%s", "\n");
	fclose(f);
}

void Logfile::save_exit_userdata()
{
	fclose(f);
}



Logfile::~Logfile()
{
}
