#include "Game.h"
#include <ctime>
#include <random>
#define PeaShooterPrice 50
#define SnowPeaPrice 75
#define WallNutPrice 50
#define SunFlowerPrice 25
#define CherryBombPrice 50
#define WaveTime 12000
using namespace std::chrono;

Game* Game::instance = nullptr;
int Game::currentLevel = 0;
Player Game::p;

string Game::playerName;

vector<Sun*> suns;
vector<ShootingPlant*> shootingPlants;
vector<Projectile*> projectiles;
vector<Plant*> plants;
vector<Zombie*> zombies;


auto beginPeaShooter = steady_clock::now();
auto beginSnowPea = steady_clock::now();
auto beginWallNut = steady_clock::now();
auto beginSunFlower = steady_clock::now();
auto beginCherryBomb = steady_clock::now();

#pragma region SINGLETON
Game& Game::getInstance() {
	if (!Game::instance) {
		Game::instance = new Game();
	}
	return *Game::instance;
}

Game::Game() {
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	conOut(15, 55);
	Log::logEvent("Jucatorul a inceput jocul!");
	cout << "Welcome to Plants vs Zombies";
	conOut(16, 55);
	cout << "Enter your name:";
	cin >> playerName;
	ifstream fin("players.txt",ios::out);
	string aux, auxPass;
	bool ok = false;
	while (fin.peek() != EOF) {
		fin >> aux;
		if (aux == playerName) {
			fin >> auxPass;
			conOut(17, 55);
			cout << "Enter your password:";
			cin >> aux;
			if (aux == auxPass) {
				p.setName(playerName);
				conOut(18, 55);
				cout << "Do you want to load your progress?(Y/N)";
				cin >> aux;
				if (aux == "Y") {
					ifstream fPlayer(playerName);
					if (!fPlayer.is_open()) {
						currentLevel = 1;
					}
					else {
						fPlayer >> currentLevel;
						p.findScore();
					}
				}
				else if(aux == "N") {
					currentLevel = 1;
				}
				else {
					return;
				}
				ok = true;
				break;
			}
			else {
				conOut(18, 55);
				cout << "The password introduced is not correct!";
				return;
			}
		}
	}
	fin.close();
	system("cls");


	if (!ok) {
		ofstream fout("players.txt", ios::app);
		fout << playerName << " ";
		p.setName(playerName);
		conOut(17, 45);
		cout << "You are a new player.Enter your password:";
		cin >> auxPass;
		fout << auxPass << endl;
		system("cls");
		Log::logEvent("Jucatorul si-a creat un cont!");
		playFirstLevel();
	}
	Log::logEvent("Jucatorul s-a logat");
	switch (currentLevel) {
	case 1:
		playFirstLevel();
		break;
	case 2:
		playSecondLevel();
		break;
	case 3:
		playThirdLevel();
		break;

	}
}
#pragma endregion SINGLETON

#pragma region LEVELS
void Game::playFirstLevel() {
	Map::getInstance().displayFirstLevel();
	Log::logEvent("Nivelul 1 a inceput");
	bool ok=Game::play(15,20,1);
	if (ok == false) {
		system("cls");
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(15, 55) << "You LOST!";
		Sleep(5000);
		Log::getInstance().logEvent("Jocul a fost pierdut la nivelul 1");
		return;
	}
	else {
		system("cls");
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(15, 55) << "Congratulations! You go to level 2";
		ofstream fout(p.getName());
		fout << 1 << " " << 0;
		Sleep(5000);
		system("cls");
		Log::getInstance().logEvent("Jucatorul a trecut la nivelul 2");
		suns.clear();
		shootingPlants.clear();
		projectiles.clear();
		plants.clear();
		playSecondLevel();

	}
}

void Game::playSecondLevel() {
	Map::getInstance().displaySecondLevel();
	bool ok = Game::play(10,25,2);
	if (ok == false) {
		system("cls");
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(15, 55) << "You LOST!";
		Log::logEvent("Jocul a fost pierdut la nivelul 2");
		Sleep(5000);
		return;
	}
	else {
		system("cls");
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(15, 55) << "Congratulations! You go to level 3";
		ofstream fout(p.getName());
		fout << 2 << " " << p.getScore();
		Sleep(5000);
		system("cls");
		Log::logEvent("Jucatorul a trecut la nivelul 3");
		suns.clear();
		shootingPlants.clear();
		projectiles.clear();
		plants.clear();
		playThirdLevel();
	}
}

void Game::playThirdLevel() {
	Map::getInstance().displayThirdLevel();
	bool ok = Game::play(5,30,3);
	if (ok == false) {
		system("cls");
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(15, 55) << "You LOST!";
		Log::logEvent("Jocul a fost pierdut la nivelul 3");
		Sleep(5000);
		return;
	}
	else {
		system("cls");
		suns.clear();
		shootingPlants.clear();
		projectiles.clear();
		plants.clear();
		UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
		conOut(15, 55) << "Congratulations! You WON!";
		Log::logEvent("Jucatorul a fost castigat");
		ofstream fout(p.getName());
		fout << 3 << " " << p.getScore();
		Sleep(5000);
		return;
	}
}
#pragma endregion LEVELS

#pragma region PLANTS
int testSun(Actiune& A) {
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	int coin;
	for (int i = 0; i < suns.size(); i++) {
		if (suns[i]->getY() == A.getX() || suns[i]->getY() == A.getX() - 1 || suns[i]->getY() == A.getX() - 2) {
			coin = suns[i]->getValue();
			conOut(5, 70);
			cout << "       ";
			delete suns[i];
			suns.erase(suns.begin() + i);
			Log::getInstance().logEvent("Un soare a fost cules");
			return coin;
		}
	}
	return 0;
}

string testFlower(Actiune A) {
	if (A.getY() == 7) {
		return "PeaShooter";
	}
	if (A.getY() == 12) {
		return "SnowPea";
	}
	if (A.getY() == 17) {
		return "WallNut";
	}
	if (A.getY() == 22) {
		return "SunFlower";
	}
	if (A.getY() == 27) {
		return "CherryBomb";
	}
}

void plantFlower(string toPlant, Actiune A, Player &p) {
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	//centrarea unei plante intr-o patratica
	int x, y;
	x = A.getX() / 5;
	x = x * 5;
	x = x + 2;
	y = A.getY() / 5;
	y = y * 5;
	y = y + 2;
	bool ok = false;

	for (int i = 0; i < plants.size(); i++) {
		if (plants[i]->getX() == x && plants[i]->getY() == y) {
			ok = true;
		}
	}

	if (ok == true) {
		conOut(15, 60) << "Exista deja o planta acolo";
		Log::getInstance().logEvent("Jucatorul a incercat sa planteze o planta unde este deja una");
		return;
	}
	auto end = chrono::steady_clock::now();
	//Pentru PeaShooter
	if (toPlant == "PeaShooter") {
		if (p.getCoins() >= PeaShooterPrice && duration_cast<milliseconds>(end - beginPeaShooter).count() > PeaShooter::getSpawnTime()) {
			plants.push_back(new PeaShooter(x, y));
			shootingPlants.push_back(new PeaShooter(x, y));
			conOut(5, 70);
			cout << "       ";
			p.scadeCoins(PeaShooterPrice);
			beginPeaShooter = end;
			Log::getInstance().logEvent("Jucatorul a cumparat o planta PeaShooter");
			return;
		}
		else if (p.getCoins() < PeaShooterPrice) {
			conOut(15, 60) << "Esti prea sarac frate";
			Log::getInstance().logEvent("Jucatorul nu a avut bani sa cumpere o planta");
			return;
		}
		else if (duration_cast<milliseconds>(end - beginPeaShooter).count() < PeaShooter::getSpawnTime()) {
			conOut(15, 60) << "Nu a crescut inca alta planta PeaShooter!";
			Log::getInstance().logEvent("Jucatorul a incercat sa cumpere o planta PeaShooter dar nu a avut monede destule");
			return;
		}
	}

	//Pentru SnowPea
	auto endSnow = steady_clock::now();
	if (toPlant == "SnowPea") {
		if (p.getCoins() >= SnowPeaPrice && duration_cast<milliseconds>(endSnow - beginSnowPea).count() > SnowPea::getSpawnTime()) {
			plants.push_back(new SnowPea(x, y));
			shootingPlants.push_back(new SnowPea(x, y));
			conOut(5, 70);
			cout << "       ";
			p.scadeCoins(SnowPeaPrice);
			beginSnowPea = endSnow;
			Log::getInstance().logEvent("Jucatorul a cumparat o planta SnowPea");
			return;
		}
		else if (p.getCoins() < SnowPeaPrice) {
			conOut(15, 60) << "Esti prea sarac frate";
			Log::getInstance().logEvent("Jucatorul nu a avut bani sa cumpere o planta");
			return;
		}
		else if (duration_cast<milliseconds>(endSnow - beginSnowPea).count() < SnowPea::getSpawnTime()) {
			conOut(15, 60) << "Nu a crescut inca alta planta SnowPea!";
			Log::getInstance().logEvent("Jucatorul a incercat sa cumpere o planta SnowPea dar nu a avut monede destule");
			return;
		}
	}

	//pentru WallNut
	auto endWallNut = steady_clock::now();
	if (toPlant == "WallNut") {
		if (p.getCoins() >= WallNutPrice && duration_cast<milliseconds>(endWallNut - beginWallNut).count() > WallNut::getSpawnTime()) {
			plants.push_back(new WallNut(x, y));
			conOut(5, 70);
			cout << "       ";
			p.scadeCoins(WallNutPrice);
			beginWallNut = endWallNut;
			Log::getInstance().logEvent("Jucatorul a cumparat o planta SnowPea");
			return;
		}
		else if (p.getCoins() < WallNutPrice) {
			conOut(15, 60) << "Esti prea sarac frate";
			Log::getInstance().logEvent("Jucatorul nu a avut bani sa cumpere o planta");
			return;
		}
		else if (duration_cast<milliseconds>(endWallNut - beginWallNut).count() < WallNut::getSpawnTime()) {
			conOut(15, 60) << "Nu a crescut inca alta planta WallNut!";
			Log::getInstance().logEvent("Jucatorul a incercat sa cumpere o planta WallNut dar nu a avut monede destule");
			return;
		}
	}

	//pentru SunFlower
	auto endSunFlower = steady_clock::now();
	if (toPlant == "SunFlower") {
		if (p.getCoins() >= SunFlowerPrice && duration_cast<milliseconds>(endSunFlower - beginSunFlower).count() > SunFlower::getSpawnTime()) {
			plants.push_back(new SunFlower(x, y));
			conOut(5, 70);
			cout << "       ";
			p.scadeCoins(SunFlowerPrice);
			beginSunFlower = endSunFlower;
			Log::getInstance().logEvent("Jucatorul a cumparat o planta SunFlower");
			return;
		}
		else if (p.getCoins() < SunFlowerPrice) {
			conOut(15, 60) << "Esti prea sarac frate";
			Log::getInstance().logEvent("Jucatorul nu a avut bani sa cumpere o planta");
			return;
		}
		else if (duration_cast<milliseconds>(endSunFlower - beginSunFlower).count() < SunFlower::getSpawnTime()) {
			conOut(15, 60) << "Nu a crescut inca alta planta SunFlower!";
			Log::getInstance().logEvent("Jucatorul a incercat sa cumpere o planta SunFlower dar nu a avut monede destule");
			return;
		}
	}

	//pentru CherryBomb
	auto endCherryBomb = steady_clock::now();
	if (toPlant == "CherryBomb") {
		if (p.getCoins() >= CherryBombPrice && duration_cast<milliseconds>(endCherryBomb - beginCherryBomb).count() > CherryBomb::getSpawnTime()) {
			plants.push_back(new CherryBomb(x, y));
			conOut(5, 70);
			cout << "       ";
			p.scadeCoins(CherryBombPrice);
			beginCherryBomb = endCherryBomb;
			Log::getInstance().logEvent("Jucatorul a cumparat o planta CherryBomb");
			return;
		}
		else if (p.getCoins() < CherryBombPrice) {
			conOut(15, 60) << "Esti prea sarac frate";
			Log::getInstance().logEvent("Jucatorul nu a avut bani sa cumpere o planta");
			return;
		}
		else if (duration_cast<milliseconds>(endCherryBomb - beginCherryBomb).count() < CherryBomb::getSpawnTime()) {
			conOut(15, 60) << "Nu a crescut inca alta planta CherryBomb!";
			Log::getInstance().logEvent("Jucatorul a incercat sa cumpere o planta CherryBomb dar nu a avut monede destule");
			return;
		}
	}
}
#pragma endregion PLANTS

#pragma region ZOMBIES

Zombie* zombieGenerator(int x, int y, int &ok) {
	int zombieNo;
	if (ok == 0) {
		random_device device;
		mt19937 generator(device());
		uniform_int_distribution<int> distribution(1, 4);
		zombieNo = distribution(generator);
	}
	else {
		random_device device;
		mt19937 generator(device());
		uniform_int_distribution<int> distribution(1, 3);
		zombieNo = distribution(generator);
	}
	switch (zombieNo) {
	case 1:
		return new Zombie(x, y, 1);
	case 2:
		return new BucketHeadZombie(x, y, 1);
	case 3:
		return new PoleVaultingZombie(x, y, 1);
	case 4:
		ok = 1;
		return new SuperZombie(x, y, 1);	
	}
	
}

void Game::startZombieWave(int level,int waveNumber, int &ok) {
	int zombieNo;
	if (level == 1) {
		if (waveNumber == 3 && ok == 0) {
			zombies.push_back(new SuperZombie(17, 49, 1));
			return;
		}
		else {
			zombies.push_back(zombieGenerator(17, 49, ok));
		}
		return;
	}
	if (level == 2) {
		if (waveNumber == 6 && ok == 0) {
			zombies.push_back(new Zombie(12, 49, 1));
			zombies.push_back(new SuperZombie(17, 49, 1));
			zombies.push_back(new Zombie(22, 49, 1));
			return;
		}
		else {
			zombies.push_back(zombieGenerator(12, 49, ok));
			zombies.push_back(zombieGenerator(17, 49, ok));
			zombies.push_back(zombieGenerator(22, 49, ok));
		}
		return;
	}
	if (level == 3) {
		if (waveNumber == 9 && ok == 0) {
			zombies.push_back(new Zombie(7, 49, 1));
			zombies.push_back(new Zombie(12, 49, 1));
			zombies.push_back(new SuperZombie(17, 49, 1));
			zombies.push_back(new Zombie(22, 49, 1));
			zombies.push_back(new Zombie(27, 49, 1));
			return;
		}
		else {
			zombies.push_back(zombieGenerator(7, 49, ok));
			zombies.push_back(zombieGenerator(12, 49, ok));
			zombies.push_back(zombieGenerator(17, 49, ok));
			zombies.push_back(zombieGenerator(22, 49, ok));
			zombies.push_back(zombieGenerator(27, 49, ok));
		}
		return;
	}
}

int testZombiePosition(int i) {
	for (int j = 0; j < plants.size(); j++) {
		if (zombies[i]->getX() == plants[j]->getY() && zombies[i]->getY() == (plants[j]->getX() + 1)) {
			return j;
		}
	}
	return -1;
}
#pragma endregion ZOMBIES

bool Game::play(int minY, int maxY, int level) {
	int waveNumber = 3 * level;
	int waveCounter = 0;
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	UserInterface::ConsoleInput& conIn = UserInterface::ConsoleInput::getInstance();
	auto beginWaveTime = steady_clock::now();
	auto begin = chrono::steady_clock::now();
	int placePlant = 0;
	int superZombieOK = 0;
	string toPlant;
	p.setCoins(200);
	while (true)
	{
		conOut(5, 70);
		cout << p.getCoins();
		conOut(2, 2);
		cout << p.getScore();

		auto end = chrono::steady_clock::now();
		if (duration_cast<milliseconds>(end - begin).count() > Sun::getSunSpawnTime()) {
			begin = end;
			suns.push_back(new Sun());
		}

		std::string action = conIn.getUserActions();
		if (action != "")
		{
			conOut(0, 70) << action;
		}

		Actiune A(action);
		//Gestiunea actiunilor de "click" ale utilizatorului
		if (A.getAct() == "clicked") {
			if (placePlant == 1) //caz in care am dat deja click pe o planta
			{
				placePlant = 0;
				if (A.getX() > 5 && A.getX() < 50 && A.getY() > minY&& A.getY() <= maxY) {
					plantFlower(toPlant, A, p);
				}
				else {
					conOut(15, 60) << "Nu ati pus planta unde trebuie";
				}
			}
			//caz in care dau click pe soare
			if ((A.getY() == 2 || A.getY() == 3) && A.getX() > 5) {
				placePlant = 0;
				p.addCoins(testSun(A));
			}//caz in care dau click pe planta in shop
			else if (A.getX() == 2 && A.getY() > 5 && A.getY() < 31) {
				conOut(15, 60) << "                                      ";
				placePlant = 1;
				toPlant = testFlower(A);//planta ce trebuie plantata
			}

		}
		// mecanismul de tragere al plantelor
		for (int i = 0; i < shootingPlants.size(); i++) {
			if (shootingPlants[i]->testTime()) {
				projectiles.push_back(shootingPlants[i]->shoot());
			}
		}
		//miscarea proiectilelor
		for (int i = 0; i < projectiles.size(); i++) {
			if (projectiles[i]->getY() >= 50) {
				delete projectiles[i];
				projectiles.erase(projectiles.begin() + i);
				continue;
			}
			if (projectiles[i]->testTime()) {
				projectiles[i]->move();
			}
		}
		//aparitie valuri zombie
		auto endWaveTime = steady_clock::now();
		if (duration_cast<milliseconds>(endWaveTime - beginWaveTime).count() > WaveTime && waveCounter<waveNumber) {
			beginWaveTime = endWaveTime;
			waveCounter++;
			Log::getInstance().logEvent("A aparut un nou val de zombie");
			startZombieWave(level, waveCounter, superZombieOK);
		}
		//miscare si atack zombie
		int index;
		for (int i = 0; i < zombies.size(); i++) {
			index = testZombiePosition(i);
			if ((zombies[i]->testTime() && index == -1)) {
				zombies[i]->move();
			}
			if (zombies[i]->getY() <= 5) {
				conIn.destroyInstance();
				conOut.destroyInstance();
				return false;
			}
			else if (index > -1 && (zombies[i]->name() == "PoleVaultingZombie" || zombies[i]->name() == "SuperZombie") && zombies[i]->jump() == 0) {
				zombies[i]->move();
				zombies[i]->makeJump();
			}
			else if (index > -1) {
				zombies[i]->print();
				plants[index]->getDamage(zombies[i]->dealDamage());
				if (plants[index]->getHealth() <= 0) {
					delete plants[index];
					plants.erase(plants.begin() + index);
					Log::getInstance().logEvent("O planta a fost distrusa");
				}
			}
		}


		//interactiune proiectile-zombie
		for (int i = 0; i < projectiles.size(); i++) {
			for (int j = 0; j < zombies.size(); j++) {
				if (projectiles[i]->getY() == zombies[j]->getY() && projectiles[i]->getX()==zombies[j]->getX()) {
					if (projectiles[i]->name() == "Pea") {
						zombies[j]->getDamage(20);
					}
					else if (projectiles[i]->name() == "FrozenPea") {
						zombies[j]->getDamage(15);
						zombies[j]->freeze();
					}
					if (zombies[j]->health() <= 0) {
						delete zombies[j];
						zombies.erase(zombies.begin() + j);
						Log::getInstance().logEvent("Un zombie a fost omorat");
						p.addScore(100);
						//j--;
					}
					delete projectiles[i];
					projectiles.erase(projectiles.begin() + i);
					//i--;
					break;
				}
			}
		}
		if (waveCounter >= waveNumber && zombies.empty()) {
			conIn.destroyInstance();
			conOut.destroyInstance();
			return true;
		}

	}
}