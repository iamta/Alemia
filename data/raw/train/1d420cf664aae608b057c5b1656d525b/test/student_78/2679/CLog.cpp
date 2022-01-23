#include <fstream>
#include <time.h>
#include <ctype.h>

#include "CLog.h"

CLog* CLog::mpInstance = NULL;


CLog& CLog::getInstance()
{
	if (mpInstance == NULL)
		mpInstance = new CLog();
	return *mpInstance;
}

CLog::CLog()
{
	std::string name, pas,temp;

	label:
	std::cout << "Say ma name : ";
	try
	{
		std::cin >> name;
		
		std::ifstream f;
		f.open("History.log");
		if (f.is_open() != 0)
			std::ofstream("History.log");
		else {

			while (!f.eof())
			{
				f >> temp;
				if (temp == name)
					throw 1;
				if (name.length() > 10)
					throw 'c';
				for (int i = 0; i < 3; i++)
					f >> temp;
			}

			f.close();
		}
	}
	catch (int)
	{
		std::cout << "The name already exists ! " << std::endl;
		Sleep(1500);
		system("CLS");
		goto label;
	}
	catch (char)
	{
		std::cout << "Name to big ! " << std::endl;
		Sleep(1500);
		system("CLS");
		goto label;
	}
	lab:
		std::cout << "Give pas : ";
		try {
			std::cin >> pas;
			int nr = 0;
			for (auto i = pas.begin(); i < pas.end(); i++)
			{
			//	if (isdigit(*i) != 0) // 
				if('0'<=(*i) && (*i)<='9')
					nr++;
			}
				if(nr==0)
					throw 1;
		}
		catch (int)
		{
			std::cout << "Must have a number in ur pas ";
			Sleep(1500);
			system("CLS");
			goto lab;
		}
		std::ofstream f;
		f.open("History.log", std::ios_base::app);
		f << name << std::endl << pas << std::endl;

		system("CLS");
		f.close();
}