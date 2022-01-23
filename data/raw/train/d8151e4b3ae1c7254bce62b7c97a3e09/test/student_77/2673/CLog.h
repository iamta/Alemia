#pragma once

#include <string>

class CLog
{
	CLog();

	static CLog *instance;

public:

	static CLog &getInstance();
	static void destroyInstance();

	void writeMessage(std::string);

};

