#include "Options.h"
#include <iostream>
#include <fstream>


using namespace std;

Options::Options()
{
	level = -1;
	SetLevel(level);
}

Options::~Options()
{
}

void Options::SetLevel(int level)
{
	if (level == -1)
	{
		ifstream file;
		file.open(filename);
		if (file.is_open())
		{
			file >> this->level;
			file.close();
		}
		else
		{
			ofstream ffile;
			ffile.open(filename);
			this->level = 0;
			ffile << this->level;
			ffile.close();
		}
	}
	else
	{
		this->level = level;
		ofstream ffile;
		ffile.open(filename);
		ffile << level;
		ffile.close();
	}
}

int Options::GetLevel()
{
	return level;
}
