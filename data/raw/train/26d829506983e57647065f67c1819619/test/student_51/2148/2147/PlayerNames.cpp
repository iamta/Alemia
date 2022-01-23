#include "PlayerNames.h"

PlayerNames::PlayerNames()
{
	name = "";
	filename = "names.log";
}

PlayerNames::~PlayerNames()
{

}

void PlayerNames::SetName(string name)
{
	this->name = name;
}

void PlayerNames::compare()
{
	bool ok = false;
	ifstream file;
	file.open(filename.c_str());
	if (file.is_open())
	{
		string aux;
		string buff;
		while (!file.eof())
		{
			getline(file, buff);
			if (buff == name)
			{
				ok = true;
				break;
			}
			else
			{
				aux += buff;
				aux += "\n";
			}
		}
		file.close();
		if (!ok)
		{
			ofstream ffile;
			ffile.open(filename.c_str());
			//aux += "\n";
			aux += name;
			ffile << aux.c_str();
			ffile.close();
		}
	}
	else
	{
		ofstream ofile;
		ofile.open(filename.c_str());
		ofile << name.c_str();
		ofile.close();
	}
}
