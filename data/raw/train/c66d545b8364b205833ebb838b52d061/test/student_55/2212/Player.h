#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class Player
{
private:
	string name;
	int coins;
	int score;
	int nivel;
public:
	Player() {
		coins = 0;
		score = 0;
	};
	Player(string name):name(name) {
		coins = 0;
		score = 0;
	};

	void setName(string nume) { name = nume; }
	void findScore() {
		ifstream fin(name);
		string aux;
		int scor;
		fin >> aux;
		fin >> scor;
		score = scor;
	}
	string getName() { return name; }

	void setCoins(int coins) { this->coins = coins; }
	void scadeCoins(int coins) { this->coins -= coins; }
	void addCoins(int coins) { this->coins += coins; }
	void addScore(int scor) { score += scor; }
	int getCoins() { return coins; }
	int getScore() { return score; }
};

