#pragma once
#include <iostream>
#include <string>

using namespace std;
class Log
{
public:
	static Log&getInstance();
	static void destroyInstance();
	void LogComand(string comanda);
	void LogUser(string user, string parola);
private:
	static Log*instance;
	Log();
	~Log();
};

