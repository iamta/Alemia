#pragma once
#include"BattleField.h"
#include"ConsoleInput.h"
#include"ConsoleOutput.h"
class Proiectil
{
protected:
	int viteza;
public:
	Proiectil() = default;
	Proiectil(int vt) :viteza(vt) { ; }
	void throwProiectil(int pos, int i);
	
	void deleteProiectil(int, int);

};

