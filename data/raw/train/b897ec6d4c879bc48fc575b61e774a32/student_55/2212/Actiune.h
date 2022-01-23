#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Actiune
{
private:
	string act;
	int x;
	int y;
public:
	Actiune(string action) {
		istringstream iss(action);
		string buff;
		do{
			iss >> buff;
			if (buff == "clicked") {
				act = buff;
				iss >> buff;
				iss >> buff;
				x = stoi(buff);
				iss >> buff;
				y = stoi(buff);
			}
		} while (iss);

	};
	
	string getAct() { return act; }
	int getX() { return x; }
	int getY() { return y; }
};

