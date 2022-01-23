#pragma once
# include <iostream>
# include <string>
# include <vector>
# include <Windows.h>
using namespace std;
class Block
{
protected:
	vector <string> B;
	COORD A;
	COORD M;
	int x_reset;
	int y_reset;

public:
	Block();
	Block(int x, int y);
	void print();

	void increase_x() { A.X = A.X + 11; }

	void increase_y() { A.Y = A.Y + 5; }

	void update_mijloc() { M.X = A.X + 4; M.Y = A.Y + 2; }

	void reset_x() { A.X = x_reset; };

	void reset_y() { A.Y = y_reset; };

	void change_mijloc(char c);
	COORD get_mijloc() { return M; }
	virtual~Block();
};

