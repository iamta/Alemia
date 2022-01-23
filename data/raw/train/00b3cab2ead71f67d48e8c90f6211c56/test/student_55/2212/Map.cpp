#include "Map.h"
Map* Map::instance = nullptr;

Map& Map::getInstance() {
	if (!Map::instance) {
		Map::instance = new Map();
	}
	return *Map::instance;
}

void Map::displayFirstLevel() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 51; j++) {
			if (i <= 5 || (i >= 15 && i <= 20) || j <= 5) {
				if (j % 5 == 0 && i % 5 == 0) {
					cout << "_";
				}
				else if (i % 5 == 0) {
					cout << "_";
				}
				else if (j % 5 == 0) {
					cout << "|";
				}
				else {
					cout << " ";
				}
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
	displayShop();
	

}

void Map::displaySecondLevel() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 51; j++) {
			if (i <= 5 || (i >= 10 && i <= 25)|| j<=5) {
				if (j % 5 == 0 && i % 5 == 0) {
					cout << "_";
				}
				else if (i % 5 == 0) {
					cout << "_";
				}
				else if (j % 5 == 0) {
					cout << "|";
				}
				else {
					cout << " ";
				}
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}


	displayShop();
}

void Map::displayThirdLevel() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 51; j++) {
			if (j % 5 == 0 && i % 5 == 0) {
				cout << "_";
			}
			else if (i % 5 == 0) {
				cout << "_";
			}
			else if (j % 5 == 0) {
				//cout << (char)186;
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}

	displayShop();

}
	
void Map::displayShop() {
	UserInterface::ConsoleOutput& conOut = UserInterface::ConsoleOutput::getInstance();
	conOut(1, 1);
	cout << "Scor";
	conOut(8, 2);
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	conOut(7, 2);
	SetConsoleTextAttribute(color, 10);
	cout << (char)159;
	conOut(8, 2);
	cout << "PS";
	conOut(9, 1);
	cout << "(50)";
	conOut(12, 2);
	SetConsoleTextAttribute(color, 11);
	cout << (char)226;
	conOut(13, 1);
	cout << "SnP";
	conOut(14, 1);
	cout << "(75)";
	conOut(17, 2);
	SetConsoleTextAttribute(color, 12);
	cout << (char)225;
	conOut(18, 2);
	SetConsoleTextAttribute(color, 12);
	cout << "WN";
	conOut(19, 1);
	cout << "(50)";
	conOut(22, 2);
	SetConsoleTextAttribute(color, 14);
	cout << (char)234;
	conOut(23, 1);
	cout << "SunF";
	conOut(24, 1);
	cout << "(50)";
	conOut(27, 2);
	SetConsoleTextAttribute(color, 4);
	cout << (char)229;
	conOut(28, 2);
	cout << "CB";
	conOut(29, 1);
	cout << "(50)";
	SetConsoleTextAttribute(color, 7);
}