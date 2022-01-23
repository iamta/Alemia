#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class PlayerNames
{
private:
	string name;
	string filename;


public:
	PlayerNames();
	~PlayerNames();
	void SetName(string name);
	void compare();

};