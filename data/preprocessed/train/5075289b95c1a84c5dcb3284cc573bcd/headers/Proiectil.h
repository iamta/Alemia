#pragma once
#include <iostream>


using namespace std;



class Proiectil
{
private:
	char forma;
	int demage;
	int x;
	int y;
public:
	Proiectil();
	~Proiectil();
	void SetForma(char forma);
	void SetDemage(int demage);
	void SetX(int x);
	void SetY(int y);
	char GetForma();
	int GetDemage();
	int GetX();
	int GetY();


};