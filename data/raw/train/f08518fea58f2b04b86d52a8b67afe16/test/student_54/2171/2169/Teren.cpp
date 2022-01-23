#include "Teren.h"
#include "ConsoleOutput.h"
#include <string>
using namespace std;

Teren*Teren::instance = nullptr;
int Teren::columns = 2;
int Teren::rows = 2;
static ConsoleOutput&conOut = ConsoleOutput::getInstance();
int Teren::x_max = 0;
int Teren::y_max = 0;

//char a[3][5] = { {' ','_','_','_',' '} ,{'|',' ',' ',' ','|',},{'|','_','_','_','|'} };
//for (int i = 0; i < 3; i++)
//{
//	for (int j = 0; j < 5; j++)
//		conOut(i, j) << a[i][j];
//}

Teren & Teren::getInstance()
{
	if (!Teren::instance)
	{
		Teren*instance = new Teren();
	}
	return*instance;
}

void Teren::destroyInstance()
{
	if (instance == nullptr)
		return;

	delete instance;
	instance = nullptr;
}

void Teren::generate_score()
{
	rows = 2;
	columns = 2;
	string score = "SCORE";
	conOut(columns, rows) << score;
	columns += score.length()+1;
	
}

void Teren::Generate_sun_field()
{
	
	for (int i = 0; i < 9; i++)
	{
		char a[3][5] = { {' ','_','_','_',' '} ,{'|',' ',' ',' ','|',},{'|','_','_','_','|'} };
		
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 5; j++)
				if (!((i == 1) && (j == 2)))
				conOut(j+columns, i+rows) << a[i][j];
		}
		columns += 6;

	}

	

}

void Teren::Generate_flower_field()
{
	rows = 6;
	columns = 2;

	for (int i = 0; i < 5; i++)
	{
		char a[3][5] = { {' ','_','_','_',' '} ,{'|',' ',' ',' ','|',},{'|','_','_','_','|'} };

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 5; j++)
				conOut(j +columns, i + rows) << a[i][j];
		}
		rows += 3;

	}

}

void Teren::Generate_plants()
{
	conOut(4,7) << "SF";
	conOut(4,10) << "PS";
	conOut(4,13) << "CB";
	conOut(4,16) << "WN";
	conOut(4,19) << "SP";
}

void Teren::Generate_battlefield(int linii_lupta)
{
	rows = 6;
	columns = 9;

	for (int i = 0; i < linii_lupta; i++)
	{
		for (int j = 0; j < 9; j++)
		{

			char a[3][5] = { {' ','_','_','_',' '} ,{'|',' ',' ',' ','|',},{'|','_','_','_','|'} };

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 5; j++)
					conOut(j + columns, i + rows) << a[i][j];
			}
			columns += 6;
		}
		if (i == linii_lupta-1)
		{
			x_max = rows;
		}
		rows += 3;
		columns = 9;
	}
	y_max = rows;
}

void Teren::Clear_field()
{
	system("CLS");
}
