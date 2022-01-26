#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

class Names
{
private:
	const char* filename = "guys.pvz";
	string name;
public:
	Names();
	~Names();
	void SetName(string name);
	string GetName();


};