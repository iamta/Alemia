#pragma once
#include "Resurse.h"
#include "Deseneaza.h"


class Sun:public Resurse, public Deseneaza
{
	static int numar_de_sori;
	static int numarul_actual;
	Sun();
	~Sun();
	static Sun* ptr;
public:
	static Sun* getInstance();
	virtual void Draw(coordonate&) override;
	static const int get_Actual() { return numarul_actual; }
	static void increase_actual() { numarul_actual++; }
	static void decrease_actual() { numarul_actual--; }
	bool up;//a fost ridicat
	bool set;//a fost setat
};

