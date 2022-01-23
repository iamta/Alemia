#pragma once

#include <time.h>
#include <chrono>

#define ROW_TITLE					20			
#define COL_FIRST_STAR_POSITION		75
#define COL_DISTANCE_BETWEEN_STARS	5

#include <list>

#include "Finante.h"
#include "Entity.h"

using namespace std::chrono;


class PlayGame
{
	PlayGame();
	

	static PlayGame *mpInstance;

	std::list<int> list_of_soare;

	list<Entity*>lista_1;
	list<Entity*>lista_2;
	list<Entity*>lista_3;
	list<Entity*>lista_4;
	list<Entity*>lista_5;


public:

	static PlayGame &getInstance();
	static void destroyInstance();
	
	void doLoadingBar();
	void getAction();


	void doSuns();
	void verifSun(int *&);

	int getTheLine(const int&);

	void choose(const int&,Entity *);

	int doZombie();

	int doZombie2();

	void doBattle(list<Entity*>&);

	void move(list<Entity*>&);

	int getX(const int &crd);

	void doPeas(list<Entity*>&);

	void verifCapat();

	void retinut(string &,string &,int *);

	void jumpIt();

	void doBattleCherry1();
	void doBattleCherry2();
	void doBattleCherry3();
	void doBattleCherry4();
	void doBattleCherry5();

	bool verifLose();
	bool verifWin();

};

