#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <list>
#include <chrono>
#include "Coordonate.h"
#include "ConsoleOutput.h"
#include "Zombie.h"


//B--bean;
//I_B--ice-bean
//C--cheery

enum TIPUL{B, I_B, STATIC};//STATIC--pentru floarea soarelui, wall_nut, si cherry
namespace Bullet {

	class Proiectile
	{
		coordonate start;//va folosi coordonatele unde a fost pusa planta
		char desen[16];
		TIPUL tip;
		std::list<coordonate> coord_proiectile;
		bool collision_Detection(coordonate p, PROIECTILE, std::list<Oaspete::Zombie*>);
		static std::chrono::steady_clock::time_point* inceput, *begin_1;
		static int numar_in_gradina;
	public:
		Proiectile(coordonate& planta);
		Proiectile() {};
		void set_coordonate(coordonate&a);
		void set_Desen(const char*aux) { strcpy_s(desen, aux); }
		void set_tip(TIPUL a) { tip = a; }
		TIPUL get_Type() { return tip; }
		virtual ~Proiectile();
		void set_Coord(coordonate& a) { start = a; }
		void actualizare_proiectile(int, std::list<Oaspete::Zombie*>, int&);
		static void actualizeaza_proiectile(int);//adauga in vectorul de static begin
	};
}
