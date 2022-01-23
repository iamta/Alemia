#include "Gameplay.h"



Gameplay::Gameplay()
{
}

void Gameplay::check_if_bullet_hit_zombie(ZombieList & Z, BulletList & B)
{
	Bullet **Bvector = B.get_active_bullets();
	Entity **Zvector = Z.get_vector();
	for (int i = 0; i < B.get_contor(); i++)
	{
		for (int j = 0; j < Z.get_contor(); j++)
		{
			if (Zvector[j] != NULL && Bvector[i] != NULL)
			{
				COORD Bc = Bvector[i]->get_bullet_pos();
				COORD Zc = Zvector[j]->get_entity_pos();
				if (Bc.Y == Zc.Y&&Bc.X == Zc.X - 1)
				{
					Bvector[i]->sterge();
					Bvector[i]->reset_bullet_poss();
					if (B.get_bullet_type(i) == 0)
					{
						int damage = Bvector[i]->get_damage();
						Zvector[j]->update_life(damage);
						if (Zvector[j]->get_health() <= 0)
						{
							Zvector[j]->sterge();
							Z.update_active_zombies(j);
						}
					}
					else if (B.get_bullet_type(i) == 1)
					{
						int slow = Bvector[i]->get_slow();
						Zvector[j]->update_speed(slow);

					}
				}
			}
		}
	}
}

void Gameplay::check_if_zombie_hit_plant(PlantList & P, ZombieList & Z, BulletList & B)
{
	Entity **Zvector = Z.get_vector();
	Entity **Pvector = P.get_active_plants();
	int *zombie_type = Z.get_zombie_type();
	for (int i = 0; i < Z.get_contor(); i++)
	{
		for (int j = 0; j < P.get_contor(); j++)
		{
			if (Zvector[i] != NULL && Pvector[j] != NULL)
			{
				COORD Pc = Pvector[j]->get_entity_pos();
				COORD Zc = Zvector[i]->get_entity_pos();

				if (Zc.X == Pc.X + 1 && Zc.Y == Pc.Y)
				{
					if (zombie_type[i] == 1)
					{
						zombie_type[i] = 0;
						Zvector[i]->sterge();
						Zvector[i]->set_pos({ Zc.X - 6,Pc.Y });
						Zvector[i]->print();
						Zvector[i]->set_is_jumped(1);
						continue;
					}
					Zvector[i]->set_is_eating(1);
					int damage = Zvector[i]->get_damage();
					Pvector[j]->update_life(damage);

					if (Pvector[j]->get_health() <= 0)
					{
						Pvector[j]->sterge();
						P.update_active_plants(j);
						B.update_active_bullets(j);
						Zvector[i]->set_is_eating(0);
					}

				}
			}
		}
	}
}

void Gameplay::intro_game()
{
	COORD A;
	A.X = 5;
	A.Y = 5;
	string line1 = "    ____  __            __                        _____                   __    _          ";
	string line2 = "   / __ \/ /___ _____  / /______   _   _______   /__  /  ____  ____ ___  / /_  (_)__  _____";
	string line3 = "  / /_/ / / __ `/ __ \/ __/ ___/  | | / / ___/     / /  / __ \/ __ `__ \/ __ \/ / _ \/ ___/";
	string line4 = " / ____/ / /_/ / / / / /_(__  )   | |/ (__  )     / /__/ /_/ / / / / / / /_/ / /  __(__  ) ";
	string line5 = "/_/   /_/\__,_/_/ /_/\__/____/    |___/____/     /____/\____/_/ /_/ /_/_.___/_/\___/____/  ";
	string line6 = "                                                                                           ";
	vector<string>text;
	text.push_back(line1);
	text.push_back(line2);
	text.push_back(line3);
	text.push_back(line4);
	text.push_back(line5);
	text.push_back(line6);
	for (std::vector<string>::iterator it = text.begin(); it != text.end(); *it++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)2 * A.X,A.Y });
		cout << *it;
		A.Y++;

	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(5000);
	system("cls");
}

void Gameplay::end_game(Logfile&L)
{
	COORD A;
	A.X = 5;
	A.Y = 15;
	string line1 = "   ______                        ____                 ";
	string line2 = "  / ____/___ _____ ___  ___     / __ \_   _____  _____";
	string line3 = " / / __/ __ `/ __ `__ \/ _ \   / / / / | / / _ \/ ___/";
	string line4 = "/ /_/ / /_/ / / / / / /  __/  / /_/ /| |/ /  __/ /    ";
	string line5 = "\____/\__,_/_/ /_/ /_/\___/   \____/ |___/\___/_/     ";
	string line6 = "                                                      ";
	vector<string>text;
	text.push_back(line1);
	text.push_back(line2);
	text.push_back(line3);
	text.push_back(line4);
	text.push_back(line5);
	text.push_back(line6);
	for (std::vector<string>::iterator it = text.begin(); it != text.end(); *it++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)2 * A.X,A.Y });
		cout << *it;
		A.Y++;

	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(5000);
	system("cls");
	
}

void Gameplay::check_end_game(ZombieList & Z, Logfile&L)
{
	Entity**vector = Z.get_vector();
	for (int i = 0; i < Z.get_contor(); i++)
	{
		if (vector[i] != NULL)
		{
			COORD aux = vector[i]->get_entity_pos();
			if (aux.X == 14)
			{
				system("cls");
				end_game(L);
				exit(0);
			}
		}
	}
}

void Gameplay::check_bullets_and_plants(BulletList & B, PlantList & P)
{
	if (B.get_contor() > 0 && P.get_contor() > 0)
	{
		Bullet**Bvector = B.get_active_bullets();
		Entity**Pvector = P.get_active_plants();
		for (int i = 0; i < B.get_contor(); i++)
		{
			for (int j = 0; j < P.get_contor(); j++)
			{
				if (Bvector[i] != NULL && Pvector[j] != NULL)
				{
					COORD Bullet = Bvector[i]->get_bullet_pos();
					COORD Plant = Pvector[j]->get_entity_pos();
					if (Bullet.X + 1 == Plant.X&&Bullet.Y == Plant.Y)
					{
						Bvector[i]->sterge();
						Bvector[i]->set_bullet_pos_from_plant({ Plant.X + 1,Plant.Y });
					}
				}
			}
		}
	}
}

void Gameplay::game()
{
	try
	{
		srand(time(NULL));

		Gameplay game;
		game.intro_game();

		Logfile log_input;
		log_input.enter_username();

		ZombieList Z;

		SunList S(19, 5);

		Grid G(15, 10);
		G.change_core(3, 4, '*');
		G.print_cage();


		Input input;
		Output output;


		PlantList Pshop;
		Pshop.print();

		Money money;
		money.print_money();

		BulletList B;

		while (true)
		{
			int k = 0;
			while (true)
			{
				input.print_mouse();
				if (input.select(Pshop, S, money, B, log_input) == false)
				{
					input.deselect(G, Pshop, B, log_input);
				}
				if (S.get_time_respawn() >= 130000)
				{
					S.select_index();
					S.set_time_respawn_to_null();
				}
				S.increase_time_spawn();

				game.check_bullets_and_plants(B, Pshop);

				if (k >= 1000 && (B.get_contor()) > 0)
				{
					B.check_bullet_pos();
					B.delete_bullet_list();
					B.print_bullet_list();
					B.update_curent_bullet_position();
					k = 0;
				}
				if (Z.get_time_respawn() == 120000)
				{
					Z.generate_zombie();
					Z.reset_time_respawn();
					Z.increase_contor();
				}
				if (Z.get_contor() > 0)
				{
					Z.move_zombie();
				}

				if (Z.get_contor() > 0 && B.get_contor() > 0)
				{
					game.check_if_bullet_hit_zombie(Z, B);

				}
				if (Z.get_contor() > 0 && Pshop.get_contor() > 0)
				{
					game.check_if_zombie_hit_plant(Pshop, Z, B);

				}
				game.check_end_game(Z, log_input);
				Z.increase_time_respawn();
				k++;
			}
		}
		system("pause");
	}
	catch(Exception e)
	{
		e.judge_me();
	}
}
Gameplay::~Gameplay()
{
}
