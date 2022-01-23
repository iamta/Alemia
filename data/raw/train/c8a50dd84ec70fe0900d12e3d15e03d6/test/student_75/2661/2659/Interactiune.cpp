#define _CRT_SECURE_NO_WARNINGS
#include "Interactiune.h"

using namespace std::chrono;
using namespace Plantele;

std::chrono::steady_clock::time_point Interactiune::begin = steady_clock::now();

Interactiune::Interactiune()
{
	for (int i = 0; i < 9; i++)
		sori[i] = Sun::getInstance();
}


Interactiune* Interactiune::ptr = nullptr;

coordonate Interactiune::coordonate_in_teren(int row, int col, int x_min, int x_max)
{
	coordonate punct;
	for (int j = x_min; j <= x_max; j += 12)
		for (int i = 20; i < 236; i += 24)
			if (row >= j && row <= j + 12)
				if (i <= col && col <= i + 24)
				{
					punct.x = j;
					punct.y = i;
					punct.what = TEREN;
					return punct;
				}
	return { 0, 0, NONE , NO};
}


Interactiune::~Interactiune()
{
	for (auto iterator : gradina)
		delete iterator;
}

Oaspete::Zombie * Interactiune::return_Zombie(int care, bool& okay)
{
	Oaspete::Zombie* zmb=nullptr;
	if (okay)
		care %= 3;
	std::string prop;
	switch (care)
	{
	case 0:
		zmb = new Oaspete::Zombie;
		prop = "A fost adaugat un zombie simplu";
		log_Actiuni::getInstance()->scrie_Actiune(prop);
		break;
	case 1:
		zmb = new Oaspete::Bucket_Head_Zombie;
		prop = "A fost adaugat un zombie bucket-head";
		log_Actiuni::getInstance()->scrie_Actiune(prop);
		break;
	case 2:
		zmb = new Oaspete::Pole_Vaulting_Zombie;
		prop = "A fost adaugat un zombie pole valuting";
		log_Actiuni::getInstance()->scrie_Actiune(prop);
		break;
	case 3:
		zmb = new Oaspete::Super_Zombie;
		prop = "A fost adaugat un super zombie";
		log_Actiuni::getInstance()->scrie_Actiune(prop);
		okay = true;
		break;
	}
	if (zmb == nullptr)
		throw zmb;
	return zmb;
}

void Interactiune::listen(int nivel, std::string action)
{
	coordonate second_double_click = proximitate(nivel, action);

	if (first_double_click.seminte == NO && second_double_click.seminte != NO)
	{
		first_double_click = second_double_click;
		switch (first_double_click.seminte)
		{
		case FLOAREA_SOARELUI:
			UserInterface::ConsoleOutput::getInstance()(66, 65) << "\u001b[33mFloarea Soarelui\u001b[37m";
			break;
		case BEAN:
			UserInterface::ConsoleOutput::getInstance()(66, 65) << "\u001b[32mMazare\u001b[37m";
			break;
		case ICEBEAN:
			UserInterface::ConsoleOutput::getInstance()(66, 65) << "\u001b[36mMazare frappe\u001b[37m";
			break;
		case CHEERY:
			UserInterface::ConsoleOutput::getInstance()(66, 65) << "\u001b[31mBomba_cireasa\u001b[37m";
			break;
		case WALL_NUT:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			UserInterface::ConsoleOutput::getInstance()(66, 65) << "Nuca_perete";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); 
			break;
		default:
			UserInterface::ConsoleOutput::getInstance()(66, 65) << "                               ";
		}

	}
	else
	{
		if(second_double_click.what==TEREN)
			if (first_double_click.seminte == FLOAREA_SOARELUI)
			{
				Floarea_Soarelui *flr=new Floarea_Soarelui;
				std::string prop = "S-a plantat o planta de floarea soarelui";
				log_Actiuni::getInstance()->scrie_Actiune(prop);
				afiseaza_info(*flr, second_double_click);
				Sun::increase_actual();
			}
			else if(first_double_click.seminte == BEAN)
			{
				Mazare* mzr= new Mazare;	
				std::string prop = "S-a plantat o planta de mazare";
				log_Actiuni::getInstance()->scrie_Actiune(prop);
				afiseaza_info(*mzr, second_double_click);
			}
			else if (first_double_click.seminte == ICEBEAN)
			{
				IceBean* ibean=new IceBean;
				std::string prop = "S-a plantat o planta de mazare de gheata";
				log_Actiuni::getInstance()->scrie_Actiune(prop);
				afiseaza_info(*ibean, second_double_click);
			}
			else if (first_double_click.seminte == CHEERY)
			{
				Cheery* chr= new Cheery;
				std::string prop = "S-a plantat o planta de cireasa";
				log_Actiuni::getInstance()->scrie_Actiune(prop);
				begin= steady_clock::now();
				afiseaza_info(*chr, second_double_click);
			}
			else if (first_double_click.seminte == WALL_NUT)
			{
				Wall_Nut* wnut= new Wall_Nut;
				std::string prop = "S-a plantat o planta de nuca";
				log_Actiuni::getInstance()->scrie_Actiune(prop);
				afiseaza_info(*wnut, second_double_click);
			}
		if (second_double_click.what == SOARE)
		{
			if (sori[second_double_click.y]->up)
			{
				sori[second_double_click.y]->up= false;
				sori[second_double_click.y]->set = false;
				UserInterface::ConsoleOutput::getInstance()(2, 24 * second_double_click.y + 32) << "  ";
				Sun::getInstance()->increase_Total(Sun::get_valoare());
				Sun::getInstance()->update();
			}
		}
		
	}
}

coordonate Interactiune::proximitate(int nivel, std::string action)
{
	coordonate punct;
	punct.seminte = NO;
	//Teren::interactiv(Meniu::getInstance().get_Level(), action);
	int row = 0, col = 0, ok = 0;
	if (action != "") {
		if (!strstr(action.c_str(), "double"))
			return { 0,0, NONE, NO};
		char* poz = _strdup(action.c_str());
		char*tok = strtok(poz, "(");
		if (tok != NULL)
		{
			tok = strtok(NULL, ",");
			if (tok)
				col = atoi(tok);
			tok = strtok(NULL, ")");
			if (tok)
				row = atoi(tok);
			if (row*col)
				ok = 1;
		}

		if (ok)
			for (int i = 4; i < 65; i += 12)
				if (i < row&&row < i + 12)
					if (0 <= col && col <= 20)
					{
						punct.x = i;
						punct.y = 0;
						punct.what = PLANTA;
						if (row > 4 && row < 16)
							punct.seminte = FLOAREA_SOARELUI;
						else if (row > 16 && row < 28)
							punct.seminte = BEAN;
						else if (row > 28 && row < 40)
							punct.seminte = ICEBEAN;
						else if (row > 40 && row < 52)
							punct.seminte = CHEERY;
						else if (row > 52 && row < 64)
							punct.seminte = WALL_NUT;
						else punct.seminte = NO;
						return punct;
					}
		if (ok)
			for (int i = 20; i < 236; i += 24)
				if (row >= 0 && row <= 4)
					if (col >= i&&col <= i + 24)
					{
						punct.x = 0;
						punct.y = (i-20)/24;
						punct.what = SOARE;
						return punct;
					}
		switch (nivel)
		{
		case 1:
			return coordonate_in_teren(row, col, 28, 40);
			break;
		case 2:
			return coordonate_in_teren(row, col, 16, 52);
			break;
		case 3:
			return coordonate_in_teren(row, col, 4, 64);
			break;
		}


	}
	return { 0,0, NONE , NO};
}

bool Interactiune::is_empty(coordonate &aux)
{
	CHAR_INFO ci;
	COORD xy = { (SHORT)aux.x+6, (SHORT)aux.y+12 };
	PSMALL_RECT rect = new _SMALL_RECT({(short)aux.x+6, (short)aux.y+12,(short)aux.x + 6, (short)aux.y + 12 });
	if (ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &(ci), { 0, 236 }, xy, rect))
		return true;
	//UserInterface::ConsoleOutput::getInstance()(66, 2) << "\u001b[31mAceasta casuta este deja ocupata!!\u001b[37m";
	return true;
}

void Interactiune::actualizeaza_soare()
{
	static steady_clock::time_point begin[9];
	steady_clock::time_point end = steady_clock::now();
	for (int i = 0; i < 9; i++)
	{
		if (sori[i]->up == true && sori[i]->set == false)
		{
			begin[i] = steady_clock::now();
			sori[i]->set = true;

		}
		if (sori[i]->up == true && sori[i]->set == true)
			if (duration_cast<milliseconds>(end - begin[i]).count() > 12500)
			{
				begin[i] = end;
				sori[i]->set = false;
				sori[i]->up = false;
				UserInterface::ConsoleOutput::getInstance()(2, 24 * i + 32) << "  ";
			}
	}
}

void Interactiune::afiseaza_info(Planta &flr, coordonate& second_double_click)
{
	if (is_empty(second_double_click)) {
		if (Sun::get_Total() >= flr.get_necesar_resurse())
		{
			flr.Draw(second_double_click);
			flr.get_Coord() = second_double_click;
			flr.proiectil.set_coordonate(second_double_click);
			gradina.push_back(&flr);
			Bullet::Proiectile::actualizeaza_proiectile(gradina.size());
			Sun::decrease_Total(flr.get_necesar_resurse());
		}
		first_double_click = { 0,0, NONE, NO };
		UserInterface::ConsoleOutput::getInstance()(66, 60) << "                     ";
		Sun::getInstance()->update();
	}
}

Interactiune* Interactiune::getInstance()
{
	if (ptr == nullptr)
		ptr = new Interactiune();
	return ptr;
}


void Interactiune::soare(int casuta)
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 75000 / (Sun::get_Actual() + 1))
	{
		begin = end;
		sori[casuta]->up = true;
		coordonate where({ 2, 24 * casuta+32, SOARE, NO });
		sori[casuta]->Draw(where);
	}
	actualizeaza_soare();
}

void Interactiune::proiectile(std::list<Oaspete::Zombie*> oaspeti)
{
	std::list<Plantele::Planta*>::iterator cheery;
	bool ok = false;
	int j = 0;
	for (std::list<Plantele::Planta*>::iterator i = gradina.begin(); i != gradina.end(); i++)
	{
		(*i)->proiectil.actualizare_proiectile(j, oaspeti, score);
		j++;
		if ((*i)->get_viata() <= 0)//optiunea pentru cazul bombei cherry, cat si pentru atunci cand o planta este distrusa
		{
			auto end = steady_clock::now();
			if (duration_cast<milliseconds>(end - begin).count() > 1000)
			{
				cheery = i;
				ok = true;
				UserInterface::ConsoleOutput::getInstance()((*i)->get_Coord().x + 6, (*i)->get_Coord().y + 9) << "   ";
			}
			if((*i)->get_viata() == -1)
				for (auto j : oaspeti)//raza de actiune a cherry-bombei
				{
					if (j->get_Coord().x == (*i)->get_Coord().x)
					{
						if (j->get_Coord().y > (*i)->get_Coord().y && j->get_Coord().y < (*i)->get_Coord().y + 24)
							j->get_viata() = 0;
					}
					if (j->get_Coord().x >= (*i)->get_Coord().x-13&&j->get_Coord().x <= (*i)->get_Coord().x+25)
						if (j->get_Coord().y >= (*i)->get_Coord().y - 23 && j->get_Coord().y <= (*i)->get_Coord().y + 47)
							j->get_viata() /= 2;
				}
		}
	}
	if (ok)
	{
		gradina.erase(cheery);
		ok = false;
	}
}

void Interactiune::adauga_Oaspeti(int care, int unde, bool& okay)//este adaugata o structura try...catch care verifica adaugarea corecta a unui zombie
{
	try {
		static auto begin = steady_clock::now();
		auto end = steady_clock::now();
		if (duration_cast<milliseconds>(end - begin).count() > 25000)
		{
			begin = end;
			Oaspete::Zombie* zmb = return_Zombie(care, okay);
			zmb->get_Coord().x = unde * 12 + 4;
			oaspeti.push_back(zmb);
		}
	}
	catch (Oaspete::Zombie*)//in cazul in care nu se va creea niciun zombie, atunci se va creeaun zombie simplu
	{
		Oaspete::Zombie* zmb = return_Zombie(0, okay);
		zmb->get_Coord().x = 4;
		oaspeti.push_back(zmb);
	};
}

void Interactiune::move()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	std::list<Oaspete::Zombie*>::iterator  aux;
	bool sters = false;
	if (duration_cast<milliseconds>(end - begin).count() > 1000)
	{
		begin = end;
		for (std::list<Oaspete::Zombie*>::iterator i= oaspeti.begin(); i!=oaspeti.end();i++)
		{
			try {
				if ((*i)->get_Speed())
				{
					(*i)->change_Speed(false);
					continue;
				}
				for (auto j : gradina)//verifica daca se afla langa o planta
					if (j->get_Coord().x == (*i)->get_Coord().x)
						if (j->get_Coord().y + 11 == (*i)->get_Coord().y)
						{
							if ((*i)->get_Jump())
							{
								UserInterface::ConsoleOutput::getInstance()(j->get_Coord().x+6, j->get_Coord().y+11) << "            ";
								(*i)->get_Coord().y-=12;
								(*i)->jumped();
							}
							else
							{
								j->get_viata()--;
								(*i)->get_Coord().y++;
							}
						}
				if ((*i)->actualizeaza_Zombie())
					throw GAME_OVER;
				else if ((*i)->get_viata() == 0)
				{
					std::string prop = "A fost omorat un zombie";
					log_Actiuni::getInstance()->scrie_Actiune(prop);
					throw DEAD;
				}
				else (*i)->Draw((*i)->get_Coord());
			}
			catch (ZOMBIE_SITUATION situatie)
			{
				if (situatie == GAME_OVER)
					throw situatie;
				if (situatie == DEAD)
				{
					(*i)->unDraw((*i)->get_Coord());
					aux = i;
					sters = true;
				}
			}
		}
		if (sters)
		{
			oaspeti.erase(aux);
			sters = false;
		}
	}
}

coordonate::coordonate(const coordonate &bla)
{
	x = bla.x;
	y = bla.y;
	what = bla.what;
	seminte = bla.seminte;
}

coordonate::coordonate()
{
	what = NONE; 
	seminte = NO; 
	x = 0;
	y = 0;
}
