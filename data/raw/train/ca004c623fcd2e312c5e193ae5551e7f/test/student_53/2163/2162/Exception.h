#pragma once
#include <iostream>
#include <string>
using namespace std;
class Exception
{
	int x;
public:
	Exception();
	Exception(int num);
	void judge_me();
	~Exception();
};

