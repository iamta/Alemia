#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class Log
{
public:
	static Log& getInstance();
	static void destroyInstance();

	static void logEvent(string eveniment);
private:
	static Log* instance;


	Log() {
		ofstream fout("log.txt");
		fout <<" ";
	};
	Log(const Log&) {};
	~Log() {};
};

