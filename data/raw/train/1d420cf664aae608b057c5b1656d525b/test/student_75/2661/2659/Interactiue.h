#pragma once
#include "ConsoleOutput.h"
#include "ConsoleInput.h"

enum ENTITATE {PLANTA, SOARE, TEREN, NONE };

struct coordonate {
	int x, y;
	ENTITATE what;
	coordonate(int x, int y, ENTITATE Z):x(x), y(y), what(what){}
	coordonate(coordonate&&);
	coordonate() {}
};

class Interactiune
{
public:
	Interactiune();
	coordonate coordonate_in_teren(int, int ,int, int);
	virtual ~Interactiune();
	coordonate proximitate(int);
};