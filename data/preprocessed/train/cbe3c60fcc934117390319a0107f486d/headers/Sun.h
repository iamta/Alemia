#pragma once
#include <iostream>

using namespace std;


class Sun
{
private:
	int val = 25;
	string forma = " O O O O ";
	int x;
	int y;
public:
	Sun();
	~Sun();
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
	const char *GetForma();
	int GetVal();



};