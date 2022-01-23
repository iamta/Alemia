#pragma once
#include <iostream>
#include "Deseneaza.h"
#include "Coordonate.h"
#include "ConsoleOutput.h"
#include "Proiectile.h"


namespace Plantele {

	class Planta :public Deseneaza
	{
		int viata;
		int necesar_resurse;
		coordonate coord;
		char culoare[10];
		char desen[10];
	public:
		Planta();
		virtual ~Planta();
		int& get_viata() { return viata; }
		coordonate& get_Coord() { return coord; }
		int& get_necesar_resurse() { return necesar_resurse; }
		virtual void Draw(coordonate&) override;
		void set_Culoare(const char*);
		void set_Desen(const char*);
		Bullet::Proiectile proiectil;
	};
}
