#pragma once

class Finante
{
	int money;
	Finante();

	static Finante* Instance;

public:

	static Finante &getInstance();
	static void destroyInstance();

	void addMoney(int );
	int getMoney();
	void withdrawMoney(int);

};

