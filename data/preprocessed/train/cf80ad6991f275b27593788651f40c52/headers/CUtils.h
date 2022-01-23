#pragma once
#include "CPoint.h"
#include "ConsoleOutput.h"
#define Height 25
#define Weight 44
class CUtils
{
public:
	static void CleanLine(CPoint* Pt,UserInterface::ConsoleOutput* conOut,int length);
	static void CleanScreen(UserInterface::ConsoleOutput* conOut);
	static void ClearMatrix(CPoint Pt, UserInterface::ConsoleOutput* conOut);
	static void Draw(CPoint Pt, char form[5][5], UserInterface::ConsoleOutput* conOut);
};

