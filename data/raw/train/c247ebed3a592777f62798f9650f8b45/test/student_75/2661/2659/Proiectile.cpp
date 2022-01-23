#include "Proiectile.h"

using namespace std::chrono;
using namespace Bullet;

int Proiectile::numar_in_gradina = 0;
std::chrono::steady_clock::time_point* Proiectile::inceput = nullptr;
std::chrono::steady_clock::time_point* Proiectile::begin_1 = nullptr;

bool Bullet::Proiectile::collision_Detection(coordonate p, PROIECTILE a, std::list<Oaspete::Zombie*> oaspeti)
{
	if (p.y+12 >= 230)
	{
		a = OFF;
		return true;
	}
	for (auto i : oaspeti)
	{
		if (p.x == i->get_Coord().x)
			if (p.y + 13 == i->get_Coord().y)
			{
				if (this->get_Type() == I_B)
					i->change_Speed(true);
				i->get_viata()--;
				return true;
			}

	}
	return false;
}



Proiectile::Proiectile(coordonate & planta):start(planta)
{
	if (planta.seminte = BEAN)
		tip = B;
	else if (planta.seminte = ICEBEAN)
		tip = I_B;
	else tip = STATIC;
	start.pr = ON;
	start.y+=2;
	coord_proiectile.push_back(start);
}

void Bullet::Proiectile::set_coordonate(coordonate & a)
{
	start = a;
	start.y = a.y + 3;
	coord_proiectile.push_back(start);
}

Proiectile::~Proiectile()
{
}

void Proiectile::actualizare_proiectile(int numar, std::list<Oaspete::Zombie*> oaspeti, int&score)
{
	if (tip != STATIC)
	{
		auto end = steady_clock::now();
		if (duration_cast<milliseconds>(end - inceput[numar]).count() > 5000)
		{
			inceput[numar] = end;
			coordonate aux = start;
			aux.pr = ON;
			coord_proiectile.push_back(aux);
		}
		if (coord_proiectile.size() != 0)
		{
			std::list<coordonate>::iterator i = coord_proiectile.begin();
			if (collision_Detection(*i, i->pr, oaspeti))
			{
				score += 50;
				UserInterface::ConsoleOutput::getInstance()(1, 0) << "Score:        ";
				UserInterface::ConsoleOutput::getInstance()(1, 0) << "Score: "<<score;
				UserInterface::ConsoleOutput::getInstance()(i->x + 7, i->y + 12) << "   ";
				coord_proiectile.erase(i);
			}
			auto end_1 = steady_clock::now();
			if (duration_cast<milliseconds>(end_1 - begin_1[numar]).count() > 50)
			{
				begin_1[numar] = end_1;
				for (std::list<coordonate>::iterator i = coord_proiectile.begin(); i != coord_proiectile.end(); i++)
				{
					UserInterface::ConsoleOutput::getInstance()(i->x + 7, i->y + 12) << desen;
					i->y += 1;
				}
			}
		}
	}
}

void Bullet::Proiectile::actualizeaza_proiectile(int nr)//actualizeaza timpii de numarare a fiecarui proiectil de la o planta
{
	if (nr != numar_in_gradina)
	{
		std::chrono::steady_clock::time_point* aux = new  std::chrono::steady_clock::time_point[numar_in_gradina];
		std::chrono::steady_clock::time_point* aux_1 = new  std::chrono::steady_clock::time_point[numar_in_gradina];
		for (int i = 0; i < numar_in_gradina; i++)
		{
			aux[i] = inceput[i];
			aux_1[i] = begin_1[i];
		}
		delete[] inceput;
		delete[] begin_1;
		inceput = new std::chrono::steady_clock::time_point[numar_in_gradina + 1];
		begin_1 = new std::chrono::steady_clock::time_point[numar_in_gradina + 1];
		for (int i = 0; i < numar_in_gradina; i++)
		{
			inceput[i] = aux[i];
			begin_1[i] = aux_1[i];
		}
		inceput[numar_in_gradina] = steady_clock::now();
		begin_1[numar_in_gradina]= steady_clock::now();
		numar_in_gradina++;
	}
}
