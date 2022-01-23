#include "Game.h"
#include "PeaShooter.h"
#include "SunFlower.h"
#include "CherryBomb.h"
#include "WallNut.h"
#include "SnowPea.h"
#include "Chronometer.h"
#include "BucketHeadZoombie.h"
#include "OrdinaryZoombie.h"
#define SCORE_POSITION_COL 2
#define SCORE_POSITION_ROW 3

ConsoleInput&conIn = ConsoleInput::getInstance();
ConsoleOutput&conOut = ConsoleOutput::getInstance();

Game*Game::instance = nullptr;


Game::Game()
{
	
}



void Game::_set_free_fields(int i)
{
	for (int j = 0; j < i; j++)
		for (int k = 0; k < 9; k++)
			free_fields[j][k] = 1;
	
}

Game & Game::getInstance()
{
	if (!Game::instance)
	{
		Game::instance = new Game();
	}
	return*Game::instance;
}

void Game::destroyInstance()
{
	if (instance==nullptr)
	{
		return;
	}
	delete instance;
	instance = nullptr;
}
int return_first_point(string a)
{
	size_t pos1 = a.find("(");
	size_t pos2 = a.find(",");

	return atoi(a.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
}

int return_second_point(string a)
{
	string b = a;
	size_t pos1 = b.find(",");
	b.erase(0, pos1 + 2);

	size_t pos2 = b.find(")");
	b.erase(pos2);

	return atoi(b.c_str());
}

void initiate_fields_availability(int level)
{
	Game::getInstance()._set_free_fields(level);

}


void Game::play()
{
	conOut(40, 15) << "introduceti numele si parola, despartite prin spatiu: ";
	string user, password;
	cin >> user >> password;
	conOut(40, 16) << "user: "<<user<<"\tpassword: "<<password;
	_getch();
	Log::getInstance().LogUser(user, password);
	conOut(40, 15) << "                                                                               ";
	conOut(40, 16) << "                                                                               ";
	int level;
	conOut(40, 15) <<"Introduceti pe ce nivel de dificultate vreti sa jucati (1, 2 sau 3): ";
	cin >> level;
	conOut(40, 16) <<"S-a ales nivelul " << level;
	_getch();
	if (level == 2)
	{
		Log::getInstance().LogComand("S-a ales nivelul 2 de dificultate!");
		level = 3;
	}
	else
		if (level == 3)
		{
			Log::getInstance().LogComand("S-a ales nivelul 3 de dificultate!");
			level = 5;
		}
		else
			Log::getInstance().LogComand("S-a ales nivelul 1 de dificultate!");

	conOut(40, 15) <<"                                                                               ";
	conOut(40, 16) <<"                                                                               ";
	Resources R;
	Teren&T = Teren::getInstance();

	T.generate_score();
	T.Generate_sun_field();
	T.Generate_flower_field();
	T.Generate_plants();
	T.Generate_battlefield(level);
	initiate_fields_availability(level);
	int existed_sunflowers = 0;
	if (Chronometer::getInstance().timer_plant());
	
	conOut(2, 31) << "COST: ";
	conOut(2, 32) << "Sunflower: 50";
	conOut(2, 33) << "Pea shooter: 75";
	conOut(2, 34) << "Cherry bomb: 150";
	conOut(2, 35) << "Wall Nut: 100";
	conOut(2, 36) << "Snow Pea: 100";
	
	bool activate_wave = true;
	bool a_plant_is_selected = false;
	bool end_game = false;
	int wave_counter = 0;
	do
	{
		if (Chronometer::getInstance().refresh())
		{
			T.generate_score();
			T.Generate_sun_field();
			T.Generate_flower_field();
			T.Generate_plants();
			T.Generate_battlefield(level);

			
			for (int i = 0; i < plante_create.size(); i++)
			{
				
				conOut(plante_create[i]->get_x(), plante_create[i]->get_y()) << plante_create[i]->get_item();
			}

		
			
			
		}
		std::string action = conIn.getUserActions();
		if (action != "")
		{
			size_t pos1 = action.find(":");
			size_t pos2 = action.find("(");
			string a = action.substr(pos1+2,pos2-pos1-3);
			if (a == "mouse double clicked at")
			{
				int x = return_first_point(action);
				int y = return_second_point(action);
				conOut(2,30) << x << " " << y;
				if (a_plant_is_selected)
				{
					
					if (((x - 11) % 6 == 0) && ((y / 5) <= 3))
					{
						if (free_fields[(y - 7) / 3][(x - 11) / 6] == 1)
						{
							a_plant_is_selected = false;
							free_fields[(y - 7) / 3][(x - 11) / 6] = 0;
							Log::getInstance().LogComand("S-a creat o planta noua!");
							Plant*p;
							
							if (selected_plant == 7)
							{
								p = new SunFlower(x, y);
								conOut(x, y) << p->get_item();
								plante_create.push_back(p);
								existed_sunflowers++;
							}
							else
								if (selected_plant == 10)
								{
									p = new PeaShooter(x, y);
									conOut(x, y) << p->get_item();
									plante_create.push_back(p);
								}
								else
									if (selected_plant == 13)
									{
										p = new CherryBomb(x, y);
										
										plante_create.push_back(p);
									}
									else
										if (selected_plant == 16)
										{
											p = new WallNut(x, y);
											conOut(x, y) << p->get_item();
											plante_create.push_back(p);
										}
										else
											if (selected_plant == 19)
											{
												p = new SnowPea(x, y);
												conOut(x, y) << p->get_item();
												plante_create.push_back(p);
											}
							
							
							

						}
					}
				}
				else
				{
					selected_plant = 0;
					if (y == 3)
					{
						if (R.check_resource(x))
						{
							Log::getInstance().LogComand("S-a selectat un soare!");
							score += 25;
						}
					}
					if (x == 4)
					{

						if (Chronometer::getInstance().timer_plant())
						{
							bool ok = false;
							if ((y == 7) && (score >= 50))
							{
								score -= 50;
								ok = true;
							}
							else
								if ((y == 10) && (score >= 75))
								{
									score -= 75;
									ok = true;
								}
								else
									if ((y == 13) && (score >= 150))
									{
										score -= 150;
										ok = true;
									}
									else
										if ((y == 16) && (score >= 100))
										{
											score -= 100;
											ok = true;
										}
										else
											if ((y == 19) && (score >= 100))
											{
												score -= 100;
												ok = true;
											}
							
							if (ok)
							{
								a_plant_is_selected = true;
								selected_plant = y;
								conOut(SCORE_POSITION_COL, SCORE_POSITION_ROW) << "   ";
							}
						}
					}
				}
			}
		}
		
		if (Chronometer::getInstance().timer_wave())
		{
			if (activate_wave)
				activate_wave = false;
			else
			{
				wave_counter++;
				activate_wave = true;
			}
		}

		if (activate_wave)
		{

			

			if (Chronometer::getInstance().timer_zoombie())
			{
				Log::getInstance().LogComand("S-a creat un zoombie obisnuit!");
				Zoombie*z = new OrdinaryZoombie(level);
				created_zoombies.push_back(z);
				conOut(z->getx(), z->gety()) << "Z";
			}

			if (Chronometer::getInstance().timer_bucketheadzoombie())
			{
				Log::getInstance().LogComand("S-a creat un bucketHead zoombie!");
				Zoombie*z = new BucketHeadZoombie(level);
				created_zoombies.push_back(z);
				conOut(z->getx(), z->gety()) << "B";
			}
		}
		if (Chronometer::getInstance().shoot())
		{
			for (int i = 0; i < plante_create.size(); i++)
			{
				if (plante_create[i]->attack())
				{
					Proiectil*pr = new Proiectil(plante_create[i]->get_x() + 2, plante_create[i]->get_y());
					proiectile.push_back(pr);
				}

			}
		}
	
		if (Chronometer::getInstance().move())
		{
			int p[20];
			int pcounter = 0;
			int v[50], z[20];
			int vcounter = 0, zcounter = 0;
			for (int i = 0; i < proiectile.size(); i++)
			{
				bool meet_zoombie = false;
				for (int j = 0; j < created_zoombies.size(); j++)
				{

					if ((proiectile[i]->getx() - 1 == created_zoombies[j]->getx()) || ((proiectile[i]->getx() == created_zoombies[j]->getx()) || (proiectile[i]->getx() + 1 == created_zoombies[j]->getx())) && (proiectile[i]->gety() == created_zoombies[j]->gety()))
					{
						meet_zoombie = true;
						created_zoombies[j]->is_hit();
						v[vcounter] = i;
						vcounter++;
						if (created_zoombies[j]->gethealth() == 0)
						{
							z[zcounter] = j;
							zcounter++;
						}
						break;
					}

				}

				if (proiectile[i]->getx() == 60)
				{
					v[vcounter] = i;
					vcounter++;
				}
				if (!meet_zoombie)
				{
					conOut(proiectile[i]->getx(), proiectile[i]->gety()) << " ";
					proiectile[i]->move();

				}
				conOut(proiectile[i]->getx(), proiectile[i]->gety()) << "o";
			}

			for (int i = 0; i < created_zoombies.size(); i++)
			{
				bool meet_plant = false;
				for (unsigned j = 0; j < plante_create.size(); j++)
				{
					

					if ((created_zoombies[i]->getx() - 2 == plante_create[j]->get_x()) && (created_zoombies[i]->gety() == plante_create[j]->get_y()))
					{
						meet_plant = true;
						plante_create[j]->injury();
						if (plante_create[j]->get_health() == 0)
						{
							p[pcounter] = j;
							pcounter++;
						}
						break;
					}
					

				}
				if (!meet_plant)
				{
					conOut(created_zoombies[i]->getx(), created_zoombies[i]->gety()) << " ";
					created_zoombies[i]->move();
					
				}
				conOut(created_zoombies[i]->getx(), created_zoombies[i]->gety()) << created_zoombies[i]->getsign();
				if (created_zoombies[i]->getx() - 1 == 8)
				{
					end_game = true;
				}

			}
			

			for (int i = pcounter - 1; i >= 0; i--)
			{
				Log::getInstance().LogComand("S-a distrus o planta!");
				free_fields[(plante_create[i]->get_y() - 7) / 3][(plante_create[i]->get_x() - 11) / 6] = 1;
				plante_create.erase(plante_create.begin() + p[i]);
			}

			for (int i = vcounter - 1; i >= 0; i--)
			{

				conOut(proiectile[i]->getx(), proiectile[i]->gety()) << " ";
				proiectile.erase(proiectile.begin() + v[i]);
			}

			for (int i = zcounter - 1; i >= 0; i--)
			{
				Log::getInstance().LogComand("S-a distrus un zoombie!");
				conOut(created_zoombies[i]->getx(), created_zoombies[i]->gety()) <<" ";
				created_zoombies.erase(created_zoombies.begin() + z[i]);
			}

		}


			R.Generate_sun(existed_sunflowers);
			
			conOut(SCORE_POSITION_COL,SCORE_POSITION_ROW) << score;
		
	} while ((!end_game)&&(wave_counter!=3));

	T.Clear_field();
	if (end_game)
	{
		Log::getInstance().LogComand("Joc pierdut!");
		conOut(25, 30) << "Game over!";
	}
	else
	{
		Log::getInstance().LogComand("joc castigat!");
		conOut(25, 30) << "Level passed succesfully!!";
	}
	conIn.destroyInstance();
	conOut.destroyInstance();
	T.destroyInstance();

}


Game::~Game()
{
}
