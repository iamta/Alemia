#pragma once
#include <iostream>
using namespace std;
class CPoint
{
private:
	int x;
	int y;
public:
	CPoint() { x = 0; y = 0; };
	CPoint(int x, int y);
	~CPoint() { ; };
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SetX(int cx) { x = cx; }
	void SetY(int cy) { y = cy; }
};

