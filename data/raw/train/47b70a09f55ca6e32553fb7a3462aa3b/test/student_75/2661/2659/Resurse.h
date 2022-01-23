#pragma once
#include "ConsoleOutput.h"



class Resurse
{  
	static int total;
	static int valoare;
public:
	static void set_Valoare(int numar) { valoare = numar; }
	static int get_valoare() { return valoare; }
	static void increase_Total(int numar) { total += numar; }
	static void decrease_Total(int numar) { total -= numar; }
	static int get_Total() { return total; }
	Resurse();
	virtual ~Resurse();
	void update();//aici va actualiza pe ecran
};

