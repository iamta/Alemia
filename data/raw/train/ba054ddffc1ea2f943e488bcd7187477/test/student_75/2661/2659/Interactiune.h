#pragma once
#include <chrono>
#include <random>
#include <vector>
#include <list>
#include <time.h>
#include "ConsoleOutput.h"
#include "ConsoleInput.h"
#include "Coordonate.h"
#include "Teren.h"
#include "Meniu.h"
#include "hPlante.h"
#include "Sun.h"
#include "hZombie.h"


enum ZOMBIE_SITUATION{DEAD, GAME_OVER};

using namespace Plantele;

class Interactiune
{
	coordonate first_double_click;
	Interactiune();
	Interactiune(int, int, ENTITATE, PLANTE);
	virtual ~Interactiune();
	int score;
	static Interactiune* ptr;
	coordonate coordonate_in_teren(int, int, int, int);
	coordonate proximitate(int, std::string);
	bool is_empty(coordonate&);
	Sun *sori[9];
	void actualizeaza_soare();
	static std::chrono::steady_clock::time_point begin;//numara timpul din momentul in care a fost amplasata o bomba cherry
	void afiseaza_info(Planta&, coordonate&);
	std::list<Plantele::Planta*> gradina;
	std::list<Oaspete::Zombie*> oaspeti;
	Oaspete::Zombie* return_Zombie(int, bool&);
public:
	void listen(int, std::string);
	static Interactiune* getInstance();
	void soare(int);
	void proiectile(std::list<Oaspete::Zombie*>);
	void adauga_Oaspeti(int, int, bool&);
	void move();
	std::list<Oaspete::Zombie*>  get_Lista_Oaspeti() { return oaspeti; }
	int& get_Score() { return score; }
};