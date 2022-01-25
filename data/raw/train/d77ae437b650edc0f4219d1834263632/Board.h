#pragma once
#include<iostream>
#include<string>
#include "SunFlower.h"
#include"Pea.h"
#include"Zombie.h"
#include"BucketZombie.h"
using namespace std;
class Board
{
private:
	string matrix[25][55];
	int score = 0;
	static int levelType;
	int money = 100;
	bool gameOver = 0;
	static Board* instance;
	bool victory = 0;

	int sunFlowercount = 0;
	int peaCount = 0;
	int zombieCount = 0;
	int bucketCount = 0;

	Pea Peas[30];
	SunFlower SunFlowers[30];
	Zombie Zombies[90];
	Zombie ZombiesWave2[90];
	BucketZombie BZombies[90];
	

	int zFull1 = 0;
	int zFull2 = 0;
	int zFull3 = 0;
	int zFull4 = 0;
	int zFull5 = 0;

	int BzFull1 = 0;
	int BzFull2 = 0;
	int BzFull3 = 0;
	int BzFull4 = 0;
	int BzFull5 = 0;

	Board()
	{
		
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				matrix[i][j] = "  ";
			}
		}
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 55; j++)
			{
				if ((i==1||i==2)&&(j==10||j==11||j==13||j==14||j==16||j==17||j==19||j==20||j==22||j==23||j==25||j==26||j==28||j==29||j==31||j==32||j==34||j==35))
				{
					matrix[i][j] = "X ";
				}
				else if ((j == 1 || j == 2) && (i == 6 || i == 7 ))
				{
					matrix[i][j] = "F ";
				}
				else if ((j == 1 || j == 2) && (i == 9 || i == 10))
				{
					matrix[i][j] = "P ";
				}
				else if((j==1||j==2)&&( i == 12 || i == 13 || i == 15 || i == 16 || i == 18 || i == 19))
				{
					matrix[i][j] = "C ";
				}
				else if((i == 9 || i == 10 || i == 6 || i == 7 || i == 12 || i == 13 || i == 15 || i == 16 || i == 18 || i == 19)&&(j==10||j==11||j==13||j==14||j==16||j==17||j==19||j==20||j==22||j==23||j==25||j==26||j==28||j==29||j==31||j==32||j==34||j==35))
				{
					matrix[i][j] = ". ";
				}
				else if((i == 9 || i == 10 || i == 6 || i == 7 || i == 12 || i == 13 || i == 15 || i == 16 || i == 18 || i == 19)&&(j == 37 || j == 38))
				{
					matrix[i][j] = "/ ";
				}
			}
		}
	}

	Board(const Board&) {};
	~Board() {};
	

	

public:
	
	static Board* getInstance();
	static void DestroyInstance();

	void PrintBoard();
	bool getGameOver()
	{
		return gameOver;
	}

	int getScore()
	{
		return score;
	}
	int getRes()
	{
		return money;
	}
	string getMat(int i,int j)
	{
		return matrix[i][j];
	}

	void renewSun(int pos);

	int clickSun(int pos);

	void collectSun(int pos);

	void getBox(int posX,int posY,int& x, int& y);

	void plantSunflower(int x, int y);

	void printSunFlowers()
	{
		for (int i = 0; i <= sunFlowercount; i++)
		{
			SunFlowers[i].print();
		}
	}

	int getSunFlowerCount()
	{
		return sunFlowercount;
	}

	void plantPea(int x, int y);

	void PeaShoot(int z);

	int getPeanumber()
	{
		return peaCount;
	}

	Pea getPea(int i)
	{
		return Peas[i];
	}

	void moveProjOnce(int i);

	void moveProjOnePosition(int i);

	bool CheckZombieSpawn();

	int setPositionForZombie();

	void printZombie(int x);

	int getZombieNumber()
	{
		return zombieCount;
	}

	Zombie getZombie(int i)
	{
		return Zombies[i];
	}

	Zombie getZombie2(int i)
	{
		return ZombiesWave2[i];
	}

	int getZombieGNumber()
	{
		return bucketCount;
	}

	BucketZombie getZombieG(int i)
	{
		return BZombies[i];
	}

	void moveZombie(int i);

	void moveZombie2(int i);

	bool checkZombieSpawnFull(int i);

	void rewindZombieCounter()
	{
		zombieCount = 0;
	}

	void rewindZFull()
	{
		zFull1 = 0;
		zFull2 = 0;
		zFull3 = 0;
		zFull4 = 0;
		zFull5 = 0;
	}

	void printZombie2(int i);

	void printZombieG(int i);

	void moveZombieG(int i);

};

