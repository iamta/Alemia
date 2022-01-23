#pragma once
#include "LogsMonitor.h"
class CExceptii
{
private:
	string mesaj;
	int code;
public:
	int GetCode() { return code; }
	CExceptii(string mesaj, int cod);
	~CExceptii() { ; };
	void PrintError();
};

