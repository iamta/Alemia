#define _CRT_SECURE_NO_WARNINGS
#include "Meniu.h"
#include "ConsoleInput.h"


enum TIP_LOGARE{NEW, OLD, WRONG_PASS};
Meniu* Meniu::ptr = nullptr;

Meniu::Meniu()
{
}


Meniu::~Meniu()
{
	if (ptr != nullptr)
		delete ptr;
	ptr = nullptr;
}


Meniu & Meniu::getInstance()
{
	if (ptr == nullptr)
		ptr = new Meniu;
	return *ptr;
}

void Meniu::chenar()
{
	for (int i = 0; i < 38; i++)
	{
		UserInterface::ConsoleOutput::getInstance()(30, 92 + i) << "_";
		UserInterface::ConsoleOutput::getInstance()(37, 92 + i) << "_";
	}
	for (int i = 0; i < 5; i++)
	{
		UserInterface::ConsoleOutput::getInstance()(32 + i, 91) << "|";
		UserInterface::ConsoleOutput::getInstance()(32 + i, 130) << "|";
	}
}

bool Meniu::verifica_nume_parola(std::string nume_utilizator, std::string parola)
{
	std::string file = "log" + nume_utilizator + ".txt";
	std::ifstream pIn(file.c_str(), std::istream::in);
	if (!pIn.is_open())
		throw NEW;
	else
	{
		char pass[20];
		pIn.getline(pass, 19);
		if (strcmp(pass, parola.c_str()) != 0)
		{
			std::cout << "\x1B[2J\x1B[H";
			chenar();
			UserInterface::ConsoleOutput::getInstance()(33, 100) << "\u001b[31mParola introdusa gresit!\u001b[37m";
			std::cin.get();
			std::cin.get();
			return true;
		}
	}
	return false;
}


void Meniu::Log()
{
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hWrite = GetStdHandle(STD_OUTPUT_HANDLE);;
	destCoord.X = 123;
	destCoord.Y = 33;
	SetConsoleCursorPosition(hWrite, destCoord);
	try {
		do
		{
			std::cout << "\x1B[2J\x1B[H";
			UserInterface::ConsoleOutput::getInstance()(33, 100) << "Id: ";
			chenar();
			for (int i = 0; true;)
			{
				std::string a = UserInterface::ConsoleInput::getInstance().getUserActions();
				if (i < 0)
					continue;
				if (a.c_str()[1] == NULL)
				{
					if (a.c_str()[0] == '/b' || a.c_str()[0] == 8)
					{
						i--;
						UserInterface::ConsoleOutput::getInstance()(33, 104 + i) << " ";
						if (nume_utilizator.length() != 0)
							nume_utilizator.erase(--nume_utilizator.end());
						continue;
					}
					if (a.c_str()[0] == '/r' || a.c_str()[0] == 13 || a.c_str()[0] == 10)
					{
						Sleep(200);
						break;
					}
					Sleep(175);
					UserInterface::ConsoleOutput::getInstance()(33, 104 + i++) << a;
					nume_utilizator += a;
				}
				if (a != "")
				{
					UserInterface::ConsoleOutput::getInstance()(66, 2) << a;
				}
			}


			std::cout << "\x1B[2J\x1B[H";
			chenar();
			UserInterface::ConsoleOutput::getInstance()(33, 100) << "Parola: ";
			for (int i = 0; true;)
			{
				std::string a = UserInterface::ConsoleInput::getInstance().getUserActions();
				if (i < 0)
					continue;
				if (a.c_str()[1] == NULL)
				{
					if (a.c_str()[0] == '/b' || a.c_str()[0] == 8)
					{
						i--;
						UserInterface::ConsoleOutput::getInstance()(33, 108 + i) << " ";
						if (parola.length() != 0)
							parola.erase(--parola.end());
						continue;
					}
					if (a.c_str()[0] == '/r' || a.c_str()[0] == 13 || a.c_str()[0] == 10)
					{
						Sleep(200);
						break;
					}
					Sleep(175);
					UserInterface::ConsoleOutput::getInstance()(33, 108 + i++) << "*";
					parola += a;
				}
				if (a != "")
				{
					UserInterface::ConsoleOutput::getInstance()(66, 2) << a;
				}
			}
		} while (verifica_nume_parola(nume_utilizator, parola));
	}
	catch (TIP_LOGARE)
	{
		std::string file = "log" +nume_utilizator + ".txt";
		std::ofstream pOut(file.c_str(), std::ostream::out);
		pOut << parola.c_str();
	}
	log_Actiuni::getInstance()->scrie_Actiune("S-a autentificat jucatorul " + nume_utilizator);
	std::cout << "\x1B[2J\x1B[H";

	nivel = 0;
	destCoord.X = 125;
	destCoord.Y = 33;
	SetConsoleCursorPosition(hWrite, destCoord);
	chenar();
	UserInterface::ConsoleOutput::getInstance()(33, 100) << "Nivel: ";
	UserInterface::ConsoleOutput::getInstance()(34, 103) << "Nivel 1";
	UserInterface::ConsoleOutput::getInstance()(35, 103) << "Nivel 2";
	UserInterface::ConsoleOutput::getInstance()(36, 103) << "Nivel 3";
	
	
	while (!nivel)
	{
		std::string action = UserInterface::ConsoleInput::getInstance().getUserActions();
		if (action != "") {
			UserInterface::ConsoleOutput::getInstance()(66, 2) << action;
			char* poz = _strdup(action.c_str());
			if (strstr(poz, "double"))
			{
				int row = 0, col = 0, ok = 0;
				char*tok = strtok(poz, "(");
				if (tok != NULL)
				{
					tok = strtok(NULL, ",");
					if (tok)
						row = atoi(tok);
					tok = strtok(NULL, ")");
					if (tok)
						col = atoi(tok);
				}
				for (int i = 0; i < 3; i++)
					if (col == 34 + i)
						if (row > 103 && row < 112)
							nivel = i + 1;

			}
		}
	}
	std::cout << "\x1B[2J\x1B[H";
	log_Actiuni::getInstance()->scrie_Actiune("S-a ales nivelul " + nivel);
}

const int Meniu::get_Level()
{
	return nivel;
}

const std::string Meniu::get_Nume()
{
	return nume_utilizator;
}

void Meniu::situatie_de_exit(int score)
{
	UserInterface::ConsoleOutput::getInstance()(66, 65) << "Vreti sa parasiti jocul?   Da   Nu";
	std::string prop = "Utilizatorul a dorit sa paraseasca jocul";
	log_Actiuni::getInstance()->scrie_Actiune(prop);
	while (true)
	{
		std::string action = UserInterface::ConsoleInput::getInstance().getUserActions();
		if (action != "") {
			UserInterface::ConsoleOutput::getInstance()(66, 2) << action;
			char* poz = _strdup(action.c_str());
			if (strstr(poz, "double"))
			{
				int row = 0, col = 0, ok = 0;
				char*tok = strtok(poz, "(");
				if (tok != NULL)
				{
					tok = strtok(NULL, ",");
					if (tok)
						row = atoi(tok);
					tok = strtok(NULL, ")");
					if (tok)
						col = atoi(tok);
				}
				if (col == 66)
					if (row > 91 && row < 94)
					{
						std::string file = "log" + nume_utilizator + ".txt";
						std::ofstream pOut(file.c_str(), std::ostream::app);
						pOut << std::endl << score;
						exit(1);
					}
					else if (row > 96 && row < 99)
					{
						UserInterface::ConsoleOutput::getInstance()(66, 65) << "                                  ";;
						break;
					}
			}
		}
		
	}
}

