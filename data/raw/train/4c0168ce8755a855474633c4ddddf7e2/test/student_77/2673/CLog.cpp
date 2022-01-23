#include "CLog.h"

#include <fstream>

CLog *CLog::instance = nullptr;

CLog::CLog()
{
	std::ofstream fout("jurnalizare.txt");
	fout << " ";
	fout.close();
}

CLog & CLog::getInstance()
{
	if (instance == nullptr)
	{
		instance = new CLog;
	}
	return *instance;
}

void CLog::destroyInstance()
{
	if (instance != nullptr)
	{
		delete(instance);
	}
	instance = nullptr;
}

void CLog::writeMessage(std::string msg)
{
	std::ofstream fout("jurnalizare.txt", std::ios_base::app);
	
	fout << msg << std::endl;

	fout.close();

}
