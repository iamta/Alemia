#pragma once

#include <string>

class User
{
	int punctaj;

	User();

	static User *Instance;

public:

	void adaugare(std::string,std::string,int);
	void score(int);
	int getscore();
	void setpunctaj();

	static User& getInstance();
	static void destroyInstance();


};

