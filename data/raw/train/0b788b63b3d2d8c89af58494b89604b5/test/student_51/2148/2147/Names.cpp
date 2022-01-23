#include "Names.h"

Names::Names()
{
	SetName(name);
}

Names::~Names()
{
}

void Names::SetName(string name)
{
	this->name = name;

	ifstream file;
	file.open(filename);
	if (file.is_open())
	{
		string buff;
		while (!file.eof())
		{
			getline(file, buff);
		}
		if (buff.find(name)==string::npos)
		{
			buff += "\n"+name;
			ofstream ffile;
			ffile.open(filename);
			ffile << buff;
			ffile.close();
		}
	}
	else
	{
		ofstream ffile;
		ffile.open(filename);
		ffile << name;
		ffile << "\n";
		ffile.close();
	}
	file.close();
}

string Names::GetName()
{
	return name;
}
