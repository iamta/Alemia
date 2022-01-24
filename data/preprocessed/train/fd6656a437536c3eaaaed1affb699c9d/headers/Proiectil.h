#pragma once
class Proiectil
{
private:
	int x;
	int y;
public:
	Proiectil(int x, int y);
	void move();
	int getx();
	int gety();
	~Proiectil();
};

