#include "terrain.h"
#include <iostream>

using namespace std;


Terrain::Terrain()
{
	Tx_lu = 10;
	Ty_lu = 3;
	Ty_rd = 8;
	Tx_rd = 85;
	Tcolor = 12;

	x_lu = 10;
	y_lu = 10;
	x_rd = 145;
	y_rd = 35;
	color = 2;
}

int Terrain::Get_xlu()
{
	return x_lu;
}

int Terrain::Get_ylu()
{
	return y_lu;
}

int Terrain::Get_xrd()
{
	return x_rd;
}

int Terrain::Get_yrd()
{
	return y_rd;
}

int Terrain::GetColor()
{
	return color;
}


int Terrain::Get_Txlu()
{
	return Tx_lu;
}

int Terrain::Get_Tylu()
{
	return Ty_lu;
}

int Terrain::Get_Txrd()
{
	return Tx_rd;
}

int Terrain::Get_Tyrd()
{
	return Ty_rd;
}

int Terrain::GetTColor()
{
	return Tcolor;
}

Terrain::~Terrain()
{
}
