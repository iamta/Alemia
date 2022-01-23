#include "Log.h"
#include <fstream>

Log *Log::instance = nullptr;

Log & Log::getInstance()
{
	if (!Log::instance)
	{
		ofstream f;
		f.open("Comenzi_joc.txt");
		f.clear();
		f.close();
		Log::instance = new Log();
	}
	return *Log::instance;
}

void Log::destroyInstance()
{
	if (Log::instance)
	{
		delete Log::instance;
		Log::instance = nullptr;
	}
}

void Log::LogComand(string comanda)
{
	ofstream f;
	f.open("Comenzi_joc.txt", ios_base::app);
	f << comanda << endl;
	f.close();
}

void Log::LogUser(string user, string parola)
{
	ofstream f;
	f.open("Users.txt", ios_base::app);
	f << "user: " << user << "\tPassword: " << parola << endl;
	f.close();
}

Log::Log()
{
}


Log::~Log()
{
}
