#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <algorithm>


#include "Meniu.h"
#include "ConsoleOutput.h"
#include "ConsoleInput.h"
#include "terrain.h"
#include "Plants.h"
#include "Sun.h"
#include "Time.h"
#include "Money.h"
#include "Options.h"
#include "Names.h"
#include "Zombie.h"
#include "PlayerNames.h"

using namespace std;
using namespace std::chrono;

#define ROW_TITLE					20			
#define COL_FIRST_STAR_POSITION		75
#define COL_DISTANCE_BETWEEN_STARS	5



class CGame
{
private:
	int x;
	Meniu men;
	UserInterface::ConsoleOutput conOut;
	UserInterface::ConsoleInput conIn;
	Terrain ter;
	timer timp;
	Money money;
	Options op;
	PlayerNames PN;
	vector <Zombie> zombie;
	vector<Sun> sun;
	vector<ShotPlants> SP;
	vector<SunFlower> SF;
	vector<BombPlants> BP;
	vector<DoubleShootPlants> DSP;
	vector<PotatoPlants> PP;
	bool endgame;
	int finish;
public:
	CGame()
	{
		timp.start();
		conOut = UserInterface::ConsoleOutput::getInstance();
		conIn = UserInterface::ConsoleInput::getInstance();
		endgame = false;
		finish = 0;
	}
	void Afisare_Meniu();
	void doLoadingBar();
	void Afisare_coord();
	void afisare_optiuni();
	int Chose();
	void Start();
	void afisare_teren();
	void afisare_plante();
	void put_plants();
	void SpawnSun();
	void Clear(int x1, int y1, int x2, int y2);
	void CatchSun();
	void AfiseazaPuncte();
	void PlanteP();
	void SpawnZombie();
	void Afiseaza_Zombie();
	void ZombieDemage();
	void ReSpawnPlants();
	bool TakeMoney(int x);
	void Log();
	void SpawnZombieBucket();
};