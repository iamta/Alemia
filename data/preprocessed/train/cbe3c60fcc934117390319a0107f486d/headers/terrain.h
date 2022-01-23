#pragma once
#include <iostream>

using namespace std;




class Terrain
{
private:
	int Tx_lu;
	int Ty_lu;
	int Tx_rd;
	int Ty_rd;
	int Tcolor;
	int x_lu;
	int y_lu;
	int x_rd;
	int y_rd;
	int color;
public:
	Terrain();
	int Get_xlu();
	int Get_ylu();
	int Get_xrd();
	int Get_yrd();
	int GetColor();
	int Get_Txlu();
	int Get_Tylu();
	int Get_Txrd();
	int Get_Tyrd();
	int GetTColor();
	~Terrain();
};