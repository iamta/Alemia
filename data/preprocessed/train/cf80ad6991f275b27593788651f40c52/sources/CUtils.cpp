#include "CUtils.h"

void CUtils::CleanLine(CPoint* Pt, UserInterface::ConsoleOutput* conOut,int length)
{
	
	for(int i=0;i<length;i++)
		(*conOut)(Pt->GetX(), Pt->GetY()+i)<<" ";
}

void CUtils::CleanScreen(UserInterface::ConsoleOutput* conOut)
{
	for(int i=0;i<Height;i++)
		for (int j = 0; j < Weight; j++)
		{
			(*conOut)(i, j) << " ";
		}
}

void CUtils::ClearMatrix(CPoint Pt, UserInterface::ConsoleOutput* conOut)
{
	for(int i=Pt.GetX();i<=Pt.GetX()+4;i++)
		for (int j = Pt.GetY(); j <= Pt.GetY() + 4; j++)
		{
			(*conOut)(i, j) << " ";
		}
}

void CUtils::Draw(CPoint Pt, char form[5][5], UserInterface::ConsoleOutput* conOut)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			(*conOut)(Pt.GetX() + i, Pt.GetY() + j) << form[i][j];
		}
}
