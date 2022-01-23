#pragma once
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include <time.h>
#include <chrono>
#include "Teren.h"
#include "Resources.h"
#include<conio.h>
#include "Plant.h"
#include "Zoombie.h"
#include "Log.h"
#include <vector>
#include "Proiectil.h"

using namespace std::chrono;
using namespace std;



class Game
{
private:
	Game();
	~Game();
	static Game*instance;
	int level = 1;
	int score = 0;
	int free_fields[5][9];
	int coord_plants[5] = { 7,10,13,16,19 };
	int selected_plant;
	vector<Plant*> plante_create;
	vector<Zoombie*> created_zoombies;
	vector<Proiectil*> proiectile;
public:
	void _set_free_fields(int i);
	static Game &getInstance();
	static void destroyInstance();
	void play();
	

};

