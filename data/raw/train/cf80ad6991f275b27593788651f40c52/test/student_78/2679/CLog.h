#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

class CLog
{
private:

	std::string username;
	std::string parola;
	CLog();
	static CLog* mpInstance;

public:

	static CLog& getInstance();
	~CLog() {};
};

