#include "User.h"

#include <fstream>

User* User::Instance = nullptr;

User::User()
{
}

void User::adaugare(std::string name, std::string pass, int level)
{
	std::ofstream fout("playeri.txt", std::ios_base::app);

	fout << name << " " << pass << " " << punctaj << std::endl;
}

void User::score(int a)
{
	punctaj += a;
}

int User::getscore()
{
	return punctaj;
}

void User::setpunctaj()
{
	punctaj = 0;
}

User & User::getInstance()
{
	if (Instance == nullptr)
	{
		Instance = new User;
	}
	return *Instance;
}

void User::destroyInstance()
{
	if (Instance != nullptr)
	{
		delete(Instance);
	}
	Instance = nullptr;
}
