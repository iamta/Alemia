#include "LogsMonitor.h"

LogsMonitor::LogsMonitor()
{
	fstream f;
	f.open(NORMAL_LOGS, std::ifstream::ate | std::ifstream::binary);
	if (f.tellg() == 20000)
	{
		f.clear();		
	}
	f.close();
	f.open(ERROR_LOGS, std::ifstream::ate | std::ifstream::binary);
	if (f.tellg() == 20000)
	{
		f.clear();
	}
	f.close();
}

void LogsMonitor::SaveLog(string content)
{
	
	ofstream f;	
	f.open(NORMAL_LOGS,ios_base::app);
	f<<content.c_str()<<endl;
	f.close();
}

void LogsMonitor::SaveError(string content)
{
	ofstream file;
	file.open(ERROR_LOGS,ios_base::app);
	file << content << endl;
	file.close();
}
