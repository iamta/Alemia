#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include <time.h>
#include <chrono>
#include "Teren.h"
#include "Meniu.h"
#include "Interactiune.h"

#define ROW_TITLE					31			
#define COL_FIRST_STAR_POSITION		103
#define COL_DISTANCE_BETWEEN_STARS	5

using namespace std::chrono;

void doLoadingBar()
{
	static auto begin = steady_clock::now();
	static int col = COL_FIRST_STAR_POSITION+5;
	static std::string printedChar = "*";

	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 150)
	{
		begin = end;
		UserInterface::ConsoleOutput::getInstance()(ROW_TITLE+9, col) << printedChar;
		if (col >= (COL_FIRST_STAR_POSITION + 5) + 4 * COL_DISTANCE_BETWEEN_STARS) {
			if (printedChar == "*")
			{
				printedChar = " ";
			}
			else
			{
				printedChar = "*";
			}
			col = COL_FIRST_STAR_POSITION+5;
		}
		else
		{
			col += COL_DISTANCE_BETWEEN_STARS;
		}		
	}
}

bool change_to_menu()
{
	static auto begin = steady_clock::now();
	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 1000)
	{
		return false;
	}
	return true;
}


int main(void)
{
	
	system("mode 650");
	UserInterface::ConsoleOutput::getInstance().Logo(ROW_TITLE, COL_FIRST_STAR_POSITION);
	UserInterface::ConsoleOutput::getInstance()(ROW_TITLE +8, COL_FIRST_STAR_POSITION+5) <<"Loading cool game now...";
	while (change_to_menu())
	{
		doLoadingBar();
		std::string action = UserInterface::ConsoleInput::getInstance().getUserActions();
		if (action != "")
		{
			UserInterface::ConsoleOutput::getInstance()(66, 2) << action;
		}
	}

	Meniu::getInstance().Log();
	Teren::getInstance(Meniu::getInstance().get_Level());
	std::random_device rd;
	std::mt19937 casuta(rd());
	std::uniform_real_distribution<double> dist_cas(0, 9);//distribuita sorilor in casute
	std::uniform_real_distribution<double> dist_zmb(0, 4);//distribuita adaugarii zombiilor
	std::uniform_real_distribution<double> dist_cas_zmb(3- Meniu::getInstance().get_Level(),2+Meniu::getInstance().get_Level());//distribuita adaugarii zombiilor in casute
	bool okay = false;//semnalul ca super zombie a fost lansat pe harta
	try {
		while (true)
		{
			std::string action = UserInterface::ConsoleInput::getInstance().getUserActions();
			if (action != "")
			{
				UserInterface::ConsoleOutput::getInstance()(66, 2) << action;
			}
			if (action == "exit")
				Meniu::getInstance().situatie_de_exit(Interactiune::getInstance()->get_Score());
			Interactiune::getInstance()->listen(Meniu::getInstance().get_Level(), action);
			Interactiune::getInstance()->soare((int)dist_cas(casuta));
			Interactiune::getInstance()->proiectile(Interactiune::getInstance()->get_Lista_Oaspeti());
			Interactiune::getInstance()->adauga_Oaspeti(dist_zmb(casuta), dist_cas_zmb(casuta), okay);
			Interactiune::getInstance()->move();
		}
	}
	catch (ZOMBIE_SITUATION situatie)
	{

		UserInterface::ConsoleOutput::getInstance()(66, 90) << "\u001b[31mJoc pierdut!\u001b[37m";
		std::string prop = "Utilizatorul a pierdut meciul";
		log_Actiuni::getInstance()->scrie_Actiune(prop);
		std::cin.get();
		std::cin.get();
		Meniu::getInstance().situatie_de_exit(Interactiune::getInstance()->get_Score());
	}

	return 0;
}

//TODO: am ramas la collision detection din Proiectile-Collision Detection