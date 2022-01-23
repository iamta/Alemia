#pragma once
#include"Output.h"
#include <vector>
class Box
{
	COORD poz;
	std::vector<std::pair<std::string, unsigned char>> content;
public:
	COORD get_poz() { return poz; }
	void set_poz(COORD poz) { this->poz = poz; }
	std::vector<std::pair<std::string, unsigned char>>* box_content() { return &content; }
	virtual void set() = 0;
	virtual void draw() = 0;
	virtual void clear() = 0;
	void empty_box();
};

