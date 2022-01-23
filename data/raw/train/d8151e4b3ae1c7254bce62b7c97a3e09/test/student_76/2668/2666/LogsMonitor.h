#pragma once
#include <iostream>
#include <string>
#include <fstream>

#define NORMAL_LOGS "logs.txt"
#define ERROR_LOGS "errors.txt"
using namespace std;

class LogsMonitor
{
private:
	LogsMonitor();
	~LogsMonitor() { ; };
public:
	static void SaveLog(string content);
	static void SaveError(string content);
};

