#pragma once
#include <vector>
#include<list>

#include "Sun.h"
#include "SunFlower.h"
#include "Pea.h"
#include "Peashooter.h"
#include "BucketHeadZombie.h"
#include "Zombie.h"
#include "IDrawable.h"
#include "ConsoleInput.h"
#include "ConsoleOutput.h"

struct coord {
	int x;
	int y;

	bool operator<(const coord& c)
	{
		return(x < c.x && y < c.y);
	}
};
struct Casuta {
	coord Start;
	coord End;

	bool apartenenta(coord  c)
	{
		return(Start < c && c < End);
	}
};

class Game
{
private:

	~Game();
	static Game* Instance;
	Game();

protected:

	int zombieCount;
	bool win = false;
	bool over = false;
	int time = 0;
	std::vector<Casuta> tabel;

public:

	static Game& getInstance();
	static Game& destroyInstance();

	std::list<IDrawable*> plants;

	std::vector<Plant*> seeds;

	std::list<Pea*> projectiles;

	std::list<Sun*> suns;

	std::list<CZombie*> zombies;


	void ZombieAttack();

	void CreateMap();

	void createSun();
	void checkSun();

	void plant(Plant*);
	void checkPlant();

	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	UserInterface::ConsoleInput& conIn = UserInterface::ConsoleInput::getInstance();

	int getTime() { return time; }
	bool isOver() {	return over; }
	void setOver(bool val) { over = val; }
	bool isWin() {	return win; }
	void setWin(bool val) { win = val; }


};

