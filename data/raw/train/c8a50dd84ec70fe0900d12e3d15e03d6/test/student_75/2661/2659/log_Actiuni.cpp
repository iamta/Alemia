#define _CRT_SECURE_NO_WARNINGS
#include "log_Actiuni.h"

log_Actiuni* log_Actiuni::ptr = nullptr;

log_Actiuni::log_Actiuni()
{
	pIn.open("LOG.txt", std::ofstream::app);
}


log_Actiuni::~log_Actiuni()
{
	delete ptr;
	ptr = nullptr;
}

log_Actiuni * log_Actiuni::getInstance()
{
	if (ptr == nullptr)
		ptr = new log_Actiuni;
	return ptr;
}

void log_Actiuni::scrie_Actiune(std::string actiune)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	pIn << timeinfo->tm_mday << "." << timeinfo->tm_hour << "." << timeinfo->tm_sec << "\t" << actiune.c_str();
	pIn << std::endl;
}
