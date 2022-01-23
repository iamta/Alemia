#pragma once
#include <fstream>
#include <time.h>

class log_Actiuni
{
	log_Actiuni();
	~log_Actiuni();
	static log_Actiuni *ptr;
	std::ofstream pIn;
public:
	static log_Actiuni* getInstance();
	void scrie_Actiune(std::string);
};

