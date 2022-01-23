#pragma once
#include "ConsoleOutput.h"
#include "ConsoleInput.h"
#include "Map.h"
#include "Sun.h";
#include "Actiune.h"
#include <chrono>
#include <time.h>
#include <vector>
#include "Player.h"
#include <fstream>
#include "SuperZombie.h"
#include "Log.h"


class Game
{
public:
	static Game& getInstance();
	static void destroyInstance();

	static void playFirstLevel();
	static void playSecondLevel();
	static void playThirdLevel();

	static void startZombieWave(int level, int waveNumber, int &ok);
	static bool play(int minY, int maxY, int level);
private:
	static Game* instance;
	static string playerName;
	static int currentLevel;
	static Player p;

	Game();
	Game(const Game&) {};
	~Game() {};
};

