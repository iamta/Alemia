#pragma once
#include <fstream>
#include <sstream>
#include "ExceptionHandler.h"

class Player
{
private:
	std::ofstream write_file;
	std::ifstream read_file;
	bool ok = true;

public:
	Player();
	Player(std::string username, std::string password);
	~Player();
	bool check_existing(std::ifstream& file, std::string username);
	bool isOk();
};

