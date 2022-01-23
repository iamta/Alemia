#include "PlayGame.h"

#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include "Map.h"
#include "User.h"
#include "CExceptii.h"
#include "CLog.h"

#include <time.h>
#include <fstream>
#include <conio.h>

#include "Sunflower.h"
#include "Peashooter.h"
#include "Zombie.h"
#include "Pea.h"
#include "BucketHeadZombie.h"
#include "WallNut.h"
#include "CherryBomb.h"

using namespace std::chrono;

PlayGame* PlayGame::mpInstance = nullptr;

PlayGame::PlayGame()
{
}


PlayGame & PlayGame::getInstance()
{
	if (mpInstance == nullptr)
		mpInstance = new PlayGame;
	return *mpInstance;
}

void PlayGame::destroyInstance()
{
	if (mpInstance != nullptr)
		delete(mpInstance);
	mpInstance = nullptr;
}


void PlayGame::doLoadingBar()
{
	static UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	
	conOut(ROW_TITLE, COL_FIRST_STAR_POSITION-20) <<     " _____ _____ _____               _____           _   _         ";
	conOut(ROW_TITLE + 1, COL_FIRST_STAR_POSITION-20) << "|  _  |     |     |   _ _ ___   |__   |___ _____| |_|_|___ ___ ";
	conOut(ROW_TITLE + 2, COL_FIRST_STAR_POSITION-20) << "|   __|  |  |  |  |  | | |_ -|  |   __| . |     | . | | -_|_ -|";
	conOut(ROW_TITLE + 3, COL_FIRST_STAR_POSITION-20) << "|__|  |_____|_____|    \_/|___|  |_____|___|_|_|_|___|_|___|___|";
	conOut(ROW_TITLE + 4, COL_FIRST_STAR_POSITION-20) << "                                                               ";
	
}


void PlayGame::getAction()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	UserInterface::ConsoleInput conIn = UserInterface::ConsoleInput::getInstance();
	HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);

	User &utilizator = User::getInstance();
	utilizator.setpunctaj();
	CLog &jurnal = CLog::getInstance();

	std::string rezultat;
	std::string username;
	std::string password;

	int level = 0;

	int *coord;
	coord = new int[2];
	coord[0] = 0;
	coord[1] = 0;

	SetConsoleTextAttribute(hcons, 5);

	int aux = 1;

	while (aux)
	{
		doLoadingBar();

		conOut(27, 67) << "Apasati un click pentru continuare";
		conOut(31, 2) << conIn.getUserActions(coord);

		if (coord[0] != 0 && coord[1] != 0)
		{
			aux = 0;
		}

	}
	conOut.clear();

	while (level == 0)
	{
		conOut(15, 40) << "Se da de doua ori tasta enter dupa introducere";
		conOut(20, 74) << "Introduceti username";
		std::cin >> username;
		conOut(20, 74) << "Introduceti password";
		std::cin >> password;
		conOut(20, 74) << "Introduceti password";
		conOut(20, 74) << "Introduceti nivel dificultate";
		std::cin >> level;
	}
	conOut.clear();

	try {

		if (level == 1)
		{
			SetConsoleTextAttribute(hcons, 30);
			Map::doLVL1();

			jurnal.writeMessage("S-a ales nivelul 1");

			Finante &resurse = Finante::getInstance();

			int counter = 0;

			conOut(11, 8) << "P";
			conOut(15, 8) << "S";
			conOut(19, 8) << "W";
			conOut(23, 8) << "C";
			conOut(33, 2) << " Resurse : " << resurse.getMoney();
			conOut(35, 2) << " Shop :";
			conOut(36, 2) << " Sun : 75";
			conOut(37, 2) << " Peashooter : 100";
			conOut(38, 2) << " Sunflower : 50";
			conOut(39, 2) << " WallNut : 150";
			conOut(40, 2) << " Cherry : 200";

			jurnal.writeMessage("S-a pus shop-ul");


			int time_of_showing_suns = 6000;

			std::string entitate;
			std::string stare_curenta;

			int nr_zombie_level = 0;

			while (true)
			{
				conOut(31, 2) << conIn.getUserActions(coord);

				User &utilizator = User::getInstance();

				conOut(31, 145) << username;
				conOut(32, 145) << "********";
				conOut(33, 145) << "Score : " << utilizator.getscore();


				static auto begin = steady_clock::now();
				auto end = steady_clock::now();

				if (duration_cast<milliseconds>(end - begin).count() > time_of_showing_suns)
				{
					begin = end;
					doSuns();
				}

				//verif click sun
				if (coord[1] != 0 && coord[0] != 0)
				{
					verifSun(coord);
					conOut(33, 2) << " Resurse : " << resurse.getMoney();
				}


				static auto begin_z = steady_clock::now();
				auto end_z = steady_clock::now();
				if (nr_zombie_level != 3)
				{
					if (duration_cast<milliseconds>(end_z - begin_z).count() > 7000)
					{
						begin_z = end_z;

						if (nr_zombie_level == 2)
						{
							int ent_line = 3;

							conOut(19, 152) << "B";

							Entity *ent = new BucketHeadZombie(600, 25, ent_line, "B", 152);

							jurnal.writeMessage("S-a creat un zombie buckethead");

							choose(ent->getLine(), ent);

							nr_zombie_level++;

							continue;
						}

						int ent_line = 3;

						conOut(19, 152) << "Z";

						Entity *ent = new Zombie(250, 25, ent_line, "Z", 152);

						jurnal.writeMessage("S-a creat un zombie banal");

						choose(ent->getLine(), ent);

						nr_zombie_level++;
					}

				}

				retinut(entitate, stare_curenta, coord);


				static auto begin_zmb = steady_clock::now();
				auto end_zmb = steady_clock::now();

				if (duration_cast<milliseconds>(end_zmb - begin_zmb).count() > 300)
				{
					begin_zmb = end_zmb;

					jumpIt();

					move(lista_3);
				}

				SetConsoleTextAttribute(hcons, 4);


				doPeas(lista_3);

				doBattleCherry3();

				doBattle(lista_3);

				if (verifLose())
				{
					rezultat = "LOSE";
					jurnal.writeMessage("Joc pierdut");
					break;
				}
				if (nr_zombie_level == 3)
				{
					if (verifWin())
					{
						rezultat = "WIN";
						jurnal.writeMessage("Joc castigat");
						break;
					}
				}

				verifCapat();

				if (entitate == "P" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 100)
					{
						conOut(coord[1], coord[0]) << "P";

						int ent_line = getTheLine(coord[1]);

						if (ent_line != 3)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new Peashooter(40, ent_line, "P", coord[0]);

						jurnal.writeMessage("S-a creat un Peashooter");

						choose(ent->getLine(), ent);

						conOut(coord[1], coord[0] + 1) << "-";

						Entity *pea = new Pea(130, coord[0] + 1, ent_line, "Pea");

						choose(ent->getLine(), pea);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(100);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
				}
				if (entitate == "S" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 50)
					{
						conOut(coord[1], coord[0]) << "S";

						int ent_line = getTheLine(coord[1]);

						if (ent_line != 3)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new Sunflower(20, ent_line, "S", coord[0]);

						jurnal.writeMessage("S-a creat un Sunflower");


						time_of_showing_suns -= 100;

						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(50);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
				if (entitate == "W" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 150)
					{
						conOut(coord[1], coord[0]) << "W";

						int ent_line = getTheLine(coord[1]);

						if (ent_line != 3)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new WallNut(1200, ent_line, "W", coord[0]);

						jurnal.writeMessage("S-a creat un WallNut");

						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(150);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
				if (entitate == "C" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 200)
					{
						conOut(coord[1], coord[0]) << "C";

						int ent_line = getTheLine(coord[1]);

						if (ent_line != 3)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new CherryBomb(300, coord[0], ent_line, "C");

						jurnal.writeMessage("S-a creat un CherryBomb");


						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(200);

						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
			}

		}

		if (level == 2)
		{
			SetConsoleTextAttribute(hcons, 30);
			Map::doLVL2();

			jurnal.writeMessage("S-a ales nivelul 2");


			Finante &resurse = Finante::getInstance();

			int counter = 0;

			conOut(11, 8) << "P";
			conOut(15, 8) << "S";
			conOut(19, 8) << "W";
			conOut(23, 8) << "C";
			conOut(33, 2) << " Resurse : " << resurse.getMoney();
			conOut(35, 2) << " Shop :";
			conOut(36, 2) << " Sun : 75";
			conOut(37, 2) << " Peashooter : 100";
			conOut(38, 2) << " Sunflower : 50";
			conOut(39, 2) << " WallNut : 150";
			conOut(40, 2) << " Cherry : 200";

			jurnal.writeMessage("S-a pus shop-ul");


			int time_of_showing_suns = 6000;

			std::string entitate;
			std::string stare_curenta;

			int nr_zombie_level = 0;

			while (true)
			{
				conOut(31, 2) << conIn.getUserActions(coord);

				User &utilizator = User::getInstance();

				conOut(31, 145) << username;
				conOut(32, 145) << "********";
				conOut(33, 145) << "Score : " << utilizator.getscore();

				static auto begin = steady_clock::now();
				auto end = steady_clock::now();

				if (duration_cast<milliseconds>(end - begin).count() > time_of_showing_suns)
				{
					begin = end;
					doSuns();
				}

				//verif click sun
				if (coord[1] != 0 && coord[0] != 0)
				{
					verifSun(coord);
					conOut(33, 2) << " Resurse : " << resurse.getMoney();
				}


				static auto begin_z = steady_clock::now();
				auto end_z = steady_clock::now();
				if (nr_zombie_level != 3)
				{
					if (duration_cast<milliseconds>(end_z - begin_z).count() > 7000)
					{
						begin_z = end_z;

						if (nr_zombie_level == 2)
						{
							int ent_line = doZombie2();

							Entity *ent = new BucketHeadZombie(600, 25, ent_line, "B", 152);

							jurnal.writeMessage("S-a creat un zombie buckethead");


							choose(ent->getLine(), ent);

							nr_zombie_level++;

							continue;
						}

						int ent_line = doZombie2();

						Entity *ent = new Zombie(250, 25, ent_line, "Z", 152);

						jurnal.writeMessage("S-a creat un zombie banal");


						choose(ent->getLine(), ent);

						nr_zombie_level++;
					}

				}

				if (verifLose())
				{
					rezultat = "LOSE";
					jurnal.writeMessage("Joc pierdut");
					break;
				}
				if (nr_zombie_level == 3)
				{
					if (verifWin())
					{
						rezultat = "WIN";
						jurnal.writeMessage("Joc castigat");

						break;
					}
				}


				retinut(entitate, stare_curenta, coord);


				static auto begin_zmb = steady_clock::now();
				auto end_zmb = steady_clock::now();

				if (duration_cast<milliseconds>(end_zmb - begin_zmb).count() > 300)
				{
					begin_zmb = end_zmb;

					jumpIt();

					move(lista_2);
					move(lista_3);
					move(lista_4);
				}

				SetConsoleTextAttribute(hcons, 4);

				doPeas(lista_2);
				doPeas(lista_3);
				doPeas(lista_4);

				doBattleCherry2();
				doBattleCherry3();
				doBattleCherry4();


				doBattle(lista_2);
				doBattle(lista_3);
				doBattle(lista_4);

				verifCapat();

				if (entitate == "P" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 100)
					{
						conOut(coord[1], coord[0]) << "P";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 2 || ent_line>4)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new Peashooter(40, ent_line, "P", coord[0]);

						jurnal.writeMessage("S-a creat un Peashooter");

						choose(ent->getLine(), ent);

						conOut(coord[1], coord[0] + 1) << "-";

						Entity *pea = new Pea(130, coord[0] + 1, ent_line, "Pea");

						choose(ent->getLine(), pea);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(100);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
				}
				if (entitate == "S" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 50)
					{
						conOut(coord[1], coord[0]) << "S";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 2 || ent_line>4)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new Sunflower(20, ent_line, "S", coord[0]);

						jurnal.writeMessage("S-a creat un Sunflower");

						time_of_showing_suns -= 100;

						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(50);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
				if (entitate == "W" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 150)
					{
						conOut(coord[1], coord[0]) << "W";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 2 || ent_line>4)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new WallNut(1200, ent_line, "W", coord[0]);

						jurnal.writeMessage("S-a creat un WallNut");


						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(150);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
				if (entitate == "C" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 200)
					{
						conOut(coord[1], coord[0]) << "C";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 2 || ent_line>4)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new CherryBomb(300, coord[0], ent_line, "C");

						jurnal.writeMessage("S-a creat un CherryBomb");


						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(200);

						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
			}

		}

		if (level == 3)
		{
			SetConsoleTextAttribute(hcons, 30);
			Map::doLVL3();

			jurnal.writeMessage("S-a ales nivelul 3");

			Finante &resurse = Finante::getInstance();

			int counter = 0;

			conOut(11, 8) << "P";
			conOut(15, 8) << "S";
			conOut(19, 8) << "W";
			conOut(23, 8) << "C";
			conOut(33, 2) << " Resurse : " << resurse.getMoney();
			conOut(35, 2) << " Shop :";
			conOut(36, 2) << " Sun : 75";
			conOut(37, 2) << " Peashooter : 100";
			conOut(38, 2) << " Sunflower : 50";
			conOut(39, 2) << " WallNut : 150";
			conOut(40, 2) << " Cherry : 200";

			jurnal.writeMessage("S-a pus shop-ul");


			int time_of_showing_suns = 6000;

			std::string entitate;
			std::string stare_curenta;

			int nr_zombie_level = 0;

			while (true)
			{
				conOut(31, 2) << conIn.getUserActions(coord);

				User &utilizator = User::getInstance();

				conOut(31, 145) << username;
				conOut(32, 145) << "********";
				conOut(33, 145) << "Score : " << utilizator.getscore();


				static auto begin = steady_clock::now();
				auto end = steady_clock::now();

				if (duration_cast<milliseconds>(end - begin).count() > time_of_showing_suns)
				{
					begin = end;
					doSuns();
				}

				if (coord[1] != 0 && coord[0] != 0)
				{
					verifSun(coord);
					conOut(33, 2) << " Resurse : " << resurse.getMoney();
				}


				static auto begin_z = steady_clock::now();
				auto end_z = steady_clock::now();
				if (nr_zombie_level != 4)
				{
					if (duration_cast<milliseconds>(end_z - begin_z).count() > 7000)
					{
						begin_z = end_z;

						if (nr_zombie_level == 3)
						{
							int ent_line = doZombie();

							Entity *ent = new BucketHeadZombie(600, 25, ent_line, "B", 152);

							choose(ent->getLine(), ent);

							jurnal.writeMessage("S-a creat un zombie buckethead");


							nr_zombie_level++;

							continue;
						}

						int ent_line = doZombie();

						Entity *ent = new Zombie(250, 25, ent_line, "Z", 152);

						choose(ent->getLine(), ent);

						jurnal.writeMessage("S-a creat un zombie banal");

						nr_zombie_level++;
					}

				}

				if (verifLose())
				{
					rezultat = "LOSE";
					jurnal.writeMessage("Joc pierdut");
					break;
				}

				if (nr_zombie_level == 4)
				{
					if (verifWin())
					{
						rezultat = "WIN";
						jurnal.writeMessage("Joc castigat");

						break;
					}
				}

				retinut(entitate, stare_curenta, coord);


				static auto begin_zmb = steady_clock::now();
				auto end_zmb = steady_clock::now();

				if (duration_cast<milliseconds>(end_zmb - begin_zmb).count() > 300)
				{
					begin_zmb = end_zmb;

					jumpIt();

					move(lista_1);
					move(lista_2);
					move(lista_3);
					move(lista_4);
					move(lista_5);
				}

				SetConsoleTextAttribute(hcons, 4);

				doPeas(lista_1);
				doPeas(lista_2);
				doPeas(lista_3);
				doPeas(lista_4);
				doPeas(lista_5);

				doBattleCherry1();
				doBattleCherry2();
				doBattleCherry3();
				doBattleCherry4();
				doBattleCherry5();


				doBattle(lista_1);
				doBattle(lista_2);
				doBattle(lista_3);
				doBattle(lista_4);
				doBattle(lista_5);

				verifCapat();

				if (entitate == "P" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 100)
					{
						conOut(coord[1], coord[0]) << "P";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 1 || ent_line>5)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new Peashooter(40, ent_line, "P", coord[0]);

						jurnal.writeMessage("S-a creat un peashooter");


						choose(ent->getLine(), ent);

						conOut(coord[1], coord[0] + 1) << "-";

						Entity *pea = new Pea(130, coord[0] + 1, ent_line, "Pea");

						choose(ent->getLine(), pea);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(100);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
				}
				if (entitate == "S" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 50)
					{
						conOut(coord[1], coord[0]) << "S";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 1 || ent_line>5)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new Sunflower(20, ent_line, "S", coord[0]);

						jurnal.writeMessage("S-a creat un sunflower");


						time_of_showing_suns -= 100;

						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(50);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
				if (entitate == "W" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 150)
					{
						conOut(coord[1], coord[0]) << "W";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 1 || ent_line>5)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new WallNut(1200, ent_line, "W", coord[0]);

						jurnal.writeMessage("S-a creat un WallNut");

						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(150);
						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
				if (entitate == "C" && stare_curenta == "retinut" && coord[0] != 8)
				{
					if (resurse.getMoney() >= 200)
					{
						conOut(coord[1], coord[0]) << "C";

						int ent_line = getTheLine(coord[1]);

						if (ent_line < 1 || ent_line>5)
						{
							throw(CExceptii("Elementul nu a fost pe linia aferenta,aveti grija ca la urmatorul joc sa puneti elementul pe aceeasi linie cu zombie-ul !!!"));
						}

						Entity *ent = new CherryBomb(300, coord[0], ent_line, "C");

						jurnal.writeMessage("S-a creat un CherryBomb");


						choose(ent->getLine(), ent);

						entitate = "";
						stare_curenta = "";

						resurse.withdrawMoney(200);

						if (resurse.getMoney() <= 100)
						{
							conOut(33, 15) << " ";
						}
						if (resurse.getMoney() == 0)
						{
							conOut(33, 15) << " ";
							conOut(33, 14) << " ";
						}
					}
					else
					{
						coord[0] = 0;
						coord[1] = 0;
						entitate = "";
						stare_curenta = "";
					}
				}
			}

		}

	}
	catch (CExceptii &e)
	{
		conOut.clear();
		conOut(20, 30) << e.returnErr();
		_getch();
	}

	conOut.clear();

	utilizator.adaugare(username, password, level);

	if (rezultat == "WIN")
	{
		Map::doWin();
	}
	if (rezultat == "LOSE") {
		Map::doLose();
	}
}

void PlayGame::doSuns()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	
	srand(time(NULL));

	int a;
	a = rand();
	a = a % 9;

	if (a == 0) 
	{
		conOut(7, 24) << "$";
		list_of_soare.push_back(24);
	}
	if (a == 1)
	{
		conOut(7, 40) << "$";
		list_of_soare.push_back(40);

	}
	if (a == 2)
	{
		conOut(7, 56) << "$";
		list_of_soare.push_back(56);

	}
	if (a == 3)
	{
		conOut(7, 72) << "$";
		list_of_soare.push_back(72);

	}
	if (a == 4)
	{
		conOut(7, 88) << "$";
		list_of_soare.push_back(88);

	}
	if (a == 5)
	{
		conOut(7, 104) << "$";
		list_of_soare.push_back(104);

	}
	if (a == 6)
	{
		conOut(7, 120) << "$";
		list_of_soare.push_back(120);

	}
	if (a == 7)
	{
		conOut(7, 136) << "$";
		list_of_soare.push_back(136);

	}
	if (a == 8)
	{	
		conOut(7, 152) << "$";
		list_of_soare.push_back(152);

	}
}

void PlayGame::verifSun(int *&coord)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);

	CLog &jurnal = CLog::getInstance();
	Finante &resurse = Finante::getInstance();

	for (auto it = list_of_soare.begin(); it != list_of_soare.end(); it++)
	{
		if ((*it) == coord[0]||(*it)==coord[1])
		{
			list_of_soare.erase(it);

			jurnal.writeMessage("S-a cules un soare");

			SetConsoleTextAttribute(hcons, 30);

			conOut(coord[1], coord[0]) << " ";

			coord[0] = 0;
			coord[1] = 0;
			
			SetConsoleTextAttribute(hcons, 4);


			resurse.addMoney(75);

			break;
		}
	}
}

int PlayGame::getTheLine(const int &crd)
{
	if (crd == 11)return 1;
	if (crd == 15)return 2;
	if (crd == 19)return 3;
	if (crd == 23)return 4;
	if (crd == 27)return 5;
}

int PlayGame::getX(const int &crd)
{
	if (crd == 1)return 11;
	if (crd == 2)return 15;
	if (crd == 3)return 19;
	if (crd == 4)return 23;
	if (crd == 5)return 27;
}

void PlayGame::doPeas(list<Entity*> &lists)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	int ok = 1;

	for (auto it = lists.begin(); it != lists.end(); it++)
	{
		if ((*it)->getType() == "Pea")ok = 0;
	}

	if (ok)
	{
		for (auto it = lists.begin(); it != lists.end(); it++)
		{
			if ((*it)->getType() == "P")
			{
				conOut(getX((*it)->getLine()), (*it)->getPosition() + 1) << "-";

				Entity *pea = new Pea(130, (*it)->getPosition() + 1, (*it)->getLine(), "Pea");

				lists.push_back(pea);
			}
		}
	}
}

void PlayGame::verifCapat()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	for (auto it = lista_1.begin(); it != lista_1.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			if ((*it)->getPosition() == 152)
			{	
				conOut(getX((*it)->getLine()), 152) << " ";
				lista_1.erase(it);
				break;
			}
		}
	}
	for (auto it = lista_2.begin(); it != lista_2.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			if ((*it)->getPosition() == 152)
			{
				conOut(getX((*it)->getLine()), 152) << " ";
				lista_2.erase(it);
				break;
			}
		}
	}
	for (auto it = lista_3.begin(); it != lista_3.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			if ((*it)->getPosition() == 152)
			{
				conOut(getX((*it)->getLine()), 152) << " ";
				lista_3.erase(it);
				break;
			}
		}
	}
	for (auto it = lista_4.begin(); it != lista_4.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			if ((*it)->getPosition() == 152)
			{
				conOut(getX((*it)->getLine()), 152) << " ";
				lista_4.erase(it);
				break;
			}
		}
	}
	for (auto it = lista_5.begin(); it != lista_5.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			if ((*it)->getPosition() == 152)
			{
				conOut(getX((*it)->getLine()), 152)<<" ";
				lista_5.erase(it);
				break;
			}
		}
	}
}

void PlayGame::retinut(string &entitate, string &stare_curenta,int *coord)
{
	if (coord[0] == 8 && coord[1] == 11)
	{
		entitate = "P";
		stare_curenta = "retinut";
	}
	if (coord[0] == 8 && coord[1] == 15)
	{
		entitate = "S";
		stare_curenta = "retinut";
	}
	if (coord[0] == 8 && coord[1] == 19)
	{
		entitate = "W";
		stare_curenta = "retinut";
	}
	if (coord[0] == 8 && coord[1] == 23)
	{
		entitate = "C";
		stare_curenta = "retinut";
	}
	if (coord[0] == 8 && coord[1] == 27)
	{
		entitate = "C";
		stare_curenta = "retinut";
	}
}

void PlayGame::jumpIt()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);

	for (auto it = lista_1.begin(); it != lista_1.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			for (auto it1 = lista_1.begin(); it1 != lista_1.end(); it1++)
			{
				if ((*it1)->getType() == "P")
				{
					if ((*it)->getPosition()+1 == (*it1)->getPosition())
					{
						SetConsoleTextAttribute(hcons, 30);

						conOut( getX((*it)->getLine()),(*it1)->getPosition()-1) << " ";

						SetConsoleTextAttribute(hcons, 4);


						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_1.begin(); it1 != lista_1.end(); it1++)
			{
				if ((*it1)->getType() == "W")
				{
					if ((*it)->getPosition()+1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_1.begin(); it1 != lista_1.end(); it1++)
			{
				if ((*it1)->getType()== "S")
				{
					if ((*it)->getPosition()+1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_1.begin(); it1 != lista_1.end(); it1++)
			{
				if ((*it1)->getType() == "C")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
		}
	}
	for (auto it = lista_2.begin(); it != lista_2.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			for (auto it1 = lista_2.begin(); it1 != lista_2.end(); it1++)
			{
				if ((*it1)->getType() == "P")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";
						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_2.begin(); it1 != lista_2.end(); it1++)
			{
				if ((*it1)->getType() == "W")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_2.begin(); it1 != lista_2.end(); it1++)
			{
				if ((*it1)->getType() == "S")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_2.begin(); it1 != lista_2.end(); it1++)
			{
				if ((*it1)->getType() == "C")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
		}
	}
	for (auto it = lista_3.begin(); it != lista_3.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			for (auto it1 = lista_3.begin(); it1 != lista_3.end(); it1++)
			{
				if ((*it1)->getType() == "P")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";
						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_3.begin(); it1 != lista_3.end(); it1++)
			{
				if ((*it1)->getType() == "W")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_3.begin(); it1 != lista_3.end(); it1++)
			{
				if ((*it1)->getType() == "S")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_3.begin(); it1 != lista_3.end(); it1++)
			{
				if ((*it1)->getType() == "C")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
		}
	}
	for (auto it = lista_4.begin(); it != lista_4.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			for (auto it1 = lista_4.begin(); it1 != lista_4.end(); it1++)
			{
				if ((*it1)->getType() == "P")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";
						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_4.begin(); it1 != lista_4.end(); it1++)
			{
				if ((*it1)->getType() == "W")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_4.begin(); it1 != lista_4.end(); it1++)
			{
				if ((*it1)->getType() == "S")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_4.begin(); it1 != lista_4.end(); it1++)
			{
				if ((*it1)->getType() == "C")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
		}
	}
	for (auto it = lista_5.begin(); it != lista_5.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			for (auto it1 = lista_5.begin(); it1 != lista_5.end(); it1++)
			{
				if ((*it1)->getType() == "P")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";
						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_5.begin(); it1 != lista_5.end(); it1++)
			{
				if ((*it1)->getType() == "W")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_5.begin(); it1 != lista_5.end(); it1++)
			{
				if ((*it1)->getType() == "S")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
			for (auto it1 = lista_5.begin(); it1 != lista_5.end(); it1++)
			{
				if ((*it1)->getType() == "C")
				{
					if ((*it)->getPosition() + 1 == (*it1)->getPosition())
					{
						conOut(getX((*it)->getLine()), (*it1)->getPosition() - 1) << " ";

						(*it)->move();
						(*it)->move();
					}
				}
			}
		}
	}
}

void PlayGame::doBattleCherry1()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	int ok;

	ok = 0;

	for (auto it = lista_1.begin(); it != lista_1.end(); it++)
	{
		if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_1.begin(); it1 != lista_1.end(); it1++)
			{
				conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";

				if ((*it1)->getType() == "Z")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							User &utilizator = User::getInstance();
							utilizator.score(25);
							lista_1.erase(it1);
						}

						for (auto it2 = lista_2.begin(); it2 != lista_2.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									User &utilizator = User::getInstance();
									utilizator.score(25);
									lista_2.erase(it2);
								}
								ok = 1;
								break;
							}
						}
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_1.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}
		else if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_1.begin(); it1 != lista_1.end(); it1++)
			{
				if ((*it1)->getType() == "B")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							User &utilizator = User::getInstance();
							utilizator.score(40);
							lista_1.erase(it1);
						}

						for (auto it2 = lista_2.begin(); it2 != lista_2.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									User &utilizator = User::getInstance();
									utilizator.score(40);
									lista_2.erase(it2);
								}
								ok = 1;
								break;
							}
						}
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_1.erase(it);

						ok = 1;
						break;
					}
				}
			}
			
			if (ok)break;

		}

	}
}

void PlayGame::doBattleCherry2()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	int ok;

	ok = 0;

	for (auto it = lista_2.begin(); it != lista_2.end(); it++)
	{
		if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_2.begin(); it1 != lista_2.end(); it1++)
			{
				if ((*it1)->getType() == "Z")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							User &utilizator = User::getInstance();
							utilizator.score(25);
							lista_2.erase(it1);
						}

						for (auto it2 = lista_1.begin(); it2 != lista_1.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									User &utilizator = User::getInstance();
									utilizator.score(25);
									lista_1.erase(it2);
								}
								ok = 1;
								break;
							}
						}

						for (auto it2 = lista_3.begin(); it2 != lista_3.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_3.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(25);
								}
								ok = 1;
								break;
							}
						}

						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_2.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}

		else if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_2.begin(); it1 != lista_2.end(); it1++)
			{
				if ((*it1)->getType() == "B")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							User &utilizator = User::getInstance();
							utilizator.score(40);
							lista_2.erase(it1);
						}

						for (auto it2 = lista_1.begin(); it2 != lista_1.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_1.erase(it2); 
									User &utilizator = User::getInstance();
									utilizator.score(40);
								}
								ok = 1;
								break;
							}
						}

						for (auto it2 = lista_3.begin(); it2 != lista_3.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_3.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(40);
								}
								ok = 1;
								break;
							}
						}
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_2.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}
	}
}

void PlayGame::doBattleCherry3()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	int ok;

	ok = 0;

	for (auto it = lista_3.begin(); it != lista_3.end(); it++)
	{
		if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_3.begin(); it1 != lista_3.end(); it1++)
			{
				if ((*it1)->getType() == "Z")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							User &utilizator = User::getInstance();
							utilizator.score(25);
							lista_3.erase(it1);
						}

						for (auto it2 = lista_2.begin(); it2 != lista_2.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_2.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(25);
								}
								ok = 1;
								break;
							}
						}

						for (auto it2 = lista_4.begin(); it2 != lista_4.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_4.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(25);
								}
								ok = 1;
								break;
							}
						}

						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_3.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}
		else if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_3.begin(); it1 != lista_3.end(); it1++)
			{
				if ((*it1)->getType() == "B")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";	
							lista_3.erase(it1);
							User &utilizator = User::getInstance();
							utilizator.score(40);
						}

						for (auto it2 = lista_2.begin(); it2 != lista_2.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_2.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(40);
								}
								ok = 1;
								break;
							}
						}

						for (auto it2 = lista_4.begin(); it2 != lista_4.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_4.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(40);
								}
								ok = 1;
								break;
							}
						}

						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_3.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}
	}
}

void PlayGame::doBattleCherry4()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	int ok;

	ok = 0;

	for (auto it = lista_4.begin(); it != lista_4.end(); it++)
	{
		if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_4.begin(); it1 != lista_4.end(); it1++)
			{
				if ((*it1)->getType() == "Z")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							lista_4.erase(it1);
							User &utilizator = User::getInstance();
							utilizator.score(25);
						}

						for (auto it2 = lista_3.begin(); it2 != lista_3.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_3.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(25);
								}
								ok = 1;
								break;
							}
						}

						for (auto it2 = lista_5.begin(); it2 != lista_5.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_5.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(25);
								}
								ok = 1;
								break;
							}
						}

						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_4.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}
		else if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_3.begin(); it1 != lista_3.end(); it1++)
			{
				if ((*it1)->getType() == "B")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							lista_3.erase(it1);
							User &utilizator = User::getInstance();
							utilizator.score(40);
						}

						for (auto it2 = lista_2.begin(); it2 != lista_2.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_2.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(40);
								}
								ok = 1;
								break;
							}
						}

						for (auto it2 = lista_4.begin(); it2 != lista_4.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_4.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(40);
								}
								ok = 1;
								break;
							}
						}

						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_3.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}
	}
}

void PlayGame::doBattleCherry5()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	int ok;

	ok = 0;

	for (auto it = lista_5.begin(); it != lista_5.end(); it++)
	{
		if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_5.begin(); it1 != lista_5.end(); it1++)
			{
				conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";

				if ((*it1)->getType() == "Z")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							lista_5.erase(it1);
							User &utilizator = User::getInstance();
							utilizator.score(25);
						}

						for (auto it2 = lista_4.begin(); it2 != lista_4.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_4.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(25);
								}
								ok = 1;
								break;
							}
						}
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_5.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}
		else if ((*it)->getType() == "C")
		{
			for (auto it1 = lista_5.begin(); it1 != lista_5.end(); it1++)
			{
				conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";

				if ((*it1)->getType() == "Z")
				{
					if ((*it)->getPosition() == (*it1)->getPosition())
					{
						(*it1)->takeDamage((*it)->getDamage());

						if ((*it1)->returnHealth() <= 0)
						{
							conOut(getX((*it1)->getPosition()), (*it1)->getPosition()) << " ";
							lista_5.erase(it1);
							User &utilizator = User::getInstance();
							utilizator.score(40);
						}

						for (auto it2 = lista_4.begin(); it2 != lista_4.end(); it2++)
						{
							if ((*it)->getPosition() - (*it2)->getPosition() >= -10 || (*it)->getPosition() - (*it2)->getPosition() <= 10)
							{
								conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
								(*it2)->takeDamage((*it)->getDamage() / 2);

								if ((*it2)->returnHealth() <= 0)
								{
									conOut(getX((*it2)->getPosition()), (*it2)->getPosition()) << " ";
									lista_4.erase(it2);
									User &utilizator = User::getInstance();
									utilizator.score(40);
								}
								ok = 1;
								break;
							}
						}
						conOut(getX((*it)->getPosition()), (*it)->getPosition()) << " ";
						lista_5.erase(it);

						ok = 1;
						break;
					}
				}
			}

			if (ok)break;
		}

	}
}

bool PlayGame::verifLose()
{
	int ok = 0;
	for (auto it = lista_1.begin(); it != lista_1.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
		{
			if ((*it)->getPosition() <= 24)ok = 1;
		}
	}
	for (auto it = lista_2.begin(); it != lista_2.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
		{
			if ((*it)->getPosition() <= 24)ok = 1;
		}
	}
	for (auto it = lista_3.begin(); it != lista_3.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
		{
			if ((*it)->getPosition() <= 24)ok = 1;
		}
	}
	for (auto it = lista_4.begin(); it != lista_4.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
		{
			if ((*it)->getPosition() <= 24)ok = 1;
		}
	}
	for (auto it = lista_5.begin(); it != lista_5.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
		{
			if ((*it)->getPosition() <= 24)ok = 1;
		}
	}


	if (ok == 1)return true;
	return false;
}

bool PlayGame::verifWin()
{
	int ok = 0;

	for (auto it = lista_1.begin(); it != lista_1.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
			ok = 1;
	}
	for (auto it = lista_2.begin(); it != lista_2.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
			ok = 1;
	}
	for (auto it = lista_3.begin(); it != lista_3.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
			ok = 1;
	}
	for (auto it = lista_4.begin(); it != lista_4.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
			ok = 1;
	}
	for (auto it = lista_5.begin(); it != lista_5.end(); it++)
	{
		if ((*it)->getType() == "Z" || (*it)->getType() == "B")
			ok = 1;
	}

	if (ok)
	{
		return false;
	}
	return true;
	
}

void PlayGame::choose(const int &crd,Entity *ent)
{
	if (crd == 1)
	{
		lista_1.push_back(ent);
	}
	if (crd == 2)
	{
		lista_2.push_back(ent);
	}
	if (crd == 3)
	{
		lista_3.push_back(ent);
	}
	if (crd == 4)
	{
		lista_4.push_back(ent);
	}
	if (crd == 5)
	{
		lista_5.push_back(ent);
	}
}

int PlayGame::doZombie()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	srand(time(NULL));

	int a;
	a = rand();
	a = a % 5;

	if (a == 0)
	{
		conOut(11, 152) << "Z";
		return 1;
	}
	if (a == 1)
	{
		conOut(15, 152) << "Z";
		return 2;
	}
	if (a == 2)
	{
		conOut(19, 152) << "Z";
		return 3;
	}
	if (a == 3)
	{
		conOut(23, 152) << "Z";
		return 4;
	}
	if (a == 4)
	{
		conOut(27, 152) << "Z";
		return 5;
	}
}

int PlayGame::doZombie2()
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	srand(time(NULL));

	int a;
	a = rand();
	a = a % 3;

	
	if (a == 0)
	{
		conOut(15, 152) << "Z";
		return 2;
	}
	if (a == 1)
	{
		conOut(19, 152) << "Z";
		return 3;
	}
	if (a == 2)
	{
		conOut(23, 152) << "Z";
		return 4;
	}
	
}

void PlayGame::doBattle(list<Entity*> &lines)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	User &utilizator = User::getInstance();

	CLog &jurnal = CLog::getInstance();

	int ok = 1;
	for (auto it = lines.begin(); it != lines.end(); it++)
	{
		if ((*it)->getType() == "Z")
		{
			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "Pea")
				{
					if (((*it)->getPosition() == (*it1)->getPosition()) || (((*it)->getPosition()-1) == (*it1)->getPosition()))
					{
						(*it)->takeDamage((*it1)->getDamage());
						lines.erase(it1);
						jurnal.writeMessage("Zombie impuscat");

						if ((*it)->returnHealth() <= 0)
						{
							HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hcons, 30);
							conOut(getX((*it)->getLine()), (*it)->getPosition()) << " ";
							conOut(getX((*it)->getLine()), (*it)->getPosition()-1) << " ";
							SetConsoleTextAttribute(hcons, 5);

							jurnal.writeMessage("Zombie omorat");

							utilizator.score(25);

							lines.erase(it);
							ok = 0;
							break;
						}
						break;
					}
				}
				
			}

			if (ok == 0)break;

			ok = 1;

			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "P")
				{
					if ((*it)->getPosition() == (*it1)->getPosition() || (*it)->getPosition() - 2 == (*it1)->getPosition())
					{
						jurnal.writeMessage("Peashooter atacat de zombie");

						(*it1)->takeDamage((*it)->returnHealth());
						(*it)->moveBack();
					}
				}
				if ((*it1)->returnHealth() <= 0)
				{
					jurnal.writeMessage("Peashooter omorat de zombie");
					lines.erase(it1);
					ok = 0;
					break;
				}
			}

			if (ok == 0)break;

			ok = 1;

			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "S")
				{
					if ((*it)->getPosition() == (*it1)->getPosition() || (*it)->getPosition() - 1 == (*it1)->getPosition())
					{
						jurnal.writeMessage("Sunflower atacat de zombie");
						(*it1)->takeDamage((*it)->returnHealth());
						(*it)->moveBack();
					}
				}
				if ((*it1)->returnHealth() <= 0)
				{
					lines.erase(it1);
					jurnal.writeMessage("Sunflower omorat de zombie");
					ok = 0;
					break;
				}
			}

			if (ok == 0)break;

			ok = 1;

			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "W")
				{
					if ((*it)->getPosition() == (*it1)->getPosition() || (*it)->getPosition() - 1 == (*it1)->getPosition())
					{
						jurnal.writeMessage("WallNut atacat de zombie");
						(*it1)->takeDamage((*it)->returnHealth());
						(*it)->moveBack();
					}
				}
				if ((*it1)->returnHealth() <= 0)
				{
					jurnal.writeMessage("WallNut omorat de zombie");

					lines.erase(it1);
					ok = 0;
					break;
				}
			}

			if (ok == 0)break;

		}

		if ((*it)->getType() == "B")
		{
			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "Pea")
				{
					if (((*it)->getPosition() == (*it1)->getPosition()) || (((*it)->getPosition() - 1) == (*it1)->getPosition()))
					{
						(*it)->takeDamage((*it1)->getDamage());
						jurnal.writeMessage("Zombie bucket impuscat");
						lines.erase(it1);
						if ((*it)->returnHealth() <= 0)

						{
							HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hcons, 30);

							jurnal.writeMessage("Zombie bucket omorat");

							conOut(getX((*it)->getLine()), (*it)->getPosition()) << " ";
							conOut(getX((*it)->getLine()), (*it)->getPosition() - 1) << " ";
							
							SetConsoleTextAttribute(hcons, 5);

							
							User &utilizator = User::getInstance();
							utilizator.score(40);

							lines.erase(it);
							ok = 0;
							break;
						}
						
						break;
					}
				}
				
			}

			if (ok == 0)break;

			ok = 1;

			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "P")
				{
					if ((*it)->getPosition() == (*it1)->getPosition() || (*it)->getPosition() - 2 == (*it1)->getPosition())
					{
						(*it1)->takeDamage((*it)->returnHealth());
						jurnal.writeMessage("Peashooter atacat de bucket zombie");

						(*it)->moveBack();
					}
				}
				if ((*it1)->returnHealth() <= 0)
				{
					lines.erase(it1);
					jurnal.writeMessage("Peashooter omorat de bucket zombie");

					ok = 0;
					break;
				}
			}

			if (ok == 0)break;

			ok = 1;

			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "S")
				{
					if ((*it)->getPosition() == (*it1)->getPosition() || (*it)->getPosition() - 1 == (*it1)->getPosition())
					{
						(*it1)->takeDamage((*it)->returnHealth());
						jurnal.writeMessage("Sunflower atacat de bucket zombie");

						(*it)->moveBack();
					}
				}
				if ((*it1)->returnHealth() <= 0)
				{
					lines.erase(it1);
					jurnal.writeMessage("Sunflower omorat de bucket zombie");

					ok = 0;
					break;
				}
			}

			if (ok == 0)break;

			ok = 1;

			for (auto it1 = lines.begin(); it1 != lines.end(); it1++)
			{
				if ((*it1)->getType() == "W")
				{
					if ((*it)->getPosition() == (*it1)->getPosition() || (*it)->getPosition() - 1 == (*it1)->getPosition())
					{
						(*it1)->takeDamage((*it)->returnHealth());
						jurnal.writeMessage("WallNut atacat de bucket zombie");

						(*it)->moveBack();
					}
				}
				if ((*it1)->returnHealth() <= 0)
				{
					lines.erase(it1);
					jurnal.writeMessage("WallNut omorat de zombie");

					ok = 0;
					break;
				}
			}

			if (ok == 0)break;

		}

	}
}

void PlayGame::move(list<Entity*>& lines)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();

	HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);

	for (auto it = lines.begin(); it != lines.end(); it++)
	{
		if ((*it)->getType() == "Z")
		{
			

			SetConsoleTextAttribute(hcons, 30);


			int a = getX((*it)->getLine());
			conOut(a, (*it)->getPosition()) << " ";
				
			(*it)->move();
			SetConsoleTextAttribute(hcons, 4);

			conOut(a, (*it)->getPosition()) << "Z";

		}
	}

	for (auto it = lines.begin(); it != lines.end(); it++)
	{
		if ((*it)->getType() == "B")
		{
			SetConsoleTextAttribute(hcons, 30);


			int a = getX((*it)->getLine());
			conOut(a, (*it)->getPosition()) << " ";

			SetConsoleTextAttribute(hcons, 4);


			(*it)->move();

			conOut(a, (*it)->getPosition()) << "B";

		}
	}


	for (auto it = lines.begin(); it != lines.end(); it++)
	{
		if ((*it)->getType() == "Pea")
		{
			SetConsoleTextAttribute(hcons, 30);


			int a = getX((*it)->getLine());
			conOut(a, (*it)->getPosition()) << " ";

			SetConsoleTextAttribute(hcons, 4);


			(*it)->move();

			conOut(a, (*it)->getPosition()) << "-";

		}
	}
}


