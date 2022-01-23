#include "IntroJoc.h"
#include "IntroIN.h"
#include "IntroOUT.h"
#include <time.h>
#include <chrono>
#include "Main_menu.h"
#include "Player.h"

using namespace std::chrono;
using namespace UserInterface;

void IntroJoc::doLoadingBar()
{
	static UserInterface::IntroOUT conOut = UserInterface::IntroOUT::getInstance();//am declarat  ai sus pot sa sterg userinterf 
	static auto begin = steady_clock::now();
	static int col = COL_FIRST_STAR_POSITION;
	static std::string printedChar = "*";

	auto end = steady_clock::now();
	if (duration_cast<milliseconds>(end - begin).count() > 150)
	{
		begin = end;
		conOut(ROW_TITLE + 1, col) << printedChar;
		if (col >= COL_FIRST_STAR_POSITION + 4 * COL_DISTANCE_BETWEEN_STARS) {
			if (printedChar == "*")
			{
				printedChar = " ";
			}
			else
			{
				printedChar = "*";
			}
			col = COL_FIRST_STAR_POSITION;
		}
		else
		{
			col += COL_DISTANCE_BETWEEN_STARS;
		}
	}
}

void IntroJoc::LoadingScreen()//asta e fct mare care foloseste fct de aparitie stelute pe rand ca sa le afiseze pe toate odata
{
	IntroOUT &c_out = IntroOUT::getInstance();
	c_out(ROW_TITLE, COL_FIRST_STAR_POSITION) << "Loading cool game now...";
	while (1)
	{
		doLoadingBar();
		c_out(ROW_TITLE + 2, COL_FIRST_STAR_POSITION) << "Press Enter to continue!";
		IntroIN &c_in = IntroIN::getInstance();
		std::string introdus;
		introdus=c_in.getUserActions();//retin valoarea introdusa
		if (introdus == "\r")
		{
			system("cls");
			//c_out(ROW_TITLE, COL_FIRST_STAR_POSITION)<<"The game is coming now!!";
			break;
		}
	}
}

void IntroJoc::create_new_user()
{
	std::string User_name,User_password;
	system("cls");
	IntroOUT &user = IntroOUT::getInstance();
	user(10, 75) << "Introduceti noul username:";
	IntroIN &get_user = IntroIN::getInstance();
	get_user.set_standard_input(true);//aici renuntam la modul in care citeam 
	std::cin >> User_name;
	user(20, 75) << "Introduceti parola dorita:";
	std::cin >> User_password;
	FILE*user_file;
	user_file = fopen("useri.txt", "a");
	fprintf(user_file, "%s : %s\n", User_name.c_str(), User_password.c_str());
	fclose(user_file);
	//modifice eu pe aici ceva incepe jocu/ meniu principla intarcere
	get_user.set_standard_input(false);//reintoarecere la scriere veche 
	Player jucator;
	jucator.start_game();

	/*Main_menu meniu;
	meniu.draw();*/
}

bool verifica_user(const char* nume, const char* parola)
{
	IntroOUT &user = IntroOUT::getInstance();
	FILE*user_file;
	user_file = fopen("useri.txt", "r");
	char retine[1024];
	char * pch;
	//printf("Splitting string \"%s\" into tokens:\n", retine);
	while (!feof(user_file))
	{
		fgets(retine, 1024, user_file); 
		pch = strtok(retine, " :");
		if (pch != NULL)
		{
			if (strcmp(pch, nume) == 0)
			{
				pch = strtok(NULL, " :\n");
				if (strcmp(pch, parola) == 0)
				{
					system("cls");
					user(30, 75) << "Welcome back!";
					Sleep(500);
					return true;//daca l am gasit e true apelam fct 
				}
			}
		}
	}
	return false;
}

void IntroJoc::change_user()
{
	std::string User_name, User_password;
	system("cls");
	IntroOUT &user = IntroOUT::getInstance();
	user(10, 75) << "Introduceti username existent:";
	IntroIN &get_user = IntroIN::getInstance();
	get_user.set_standard_input(true);//aici renuntam la modul in care citeam 
	std::cin >> User_name;
	user(20, 75) << "Introduceti parola:";
	std::cin >> User_password;
	if (verifica_user(User_name.c_str(), User_password.c_str()))
	{
		nume_player = User_name;//retin numele userului logat tre sa vad cum fac su asta
		Player jucator;
		get_user.set_standard_input(false);//ne intoarcem la modul de citit implemnetat de profu 
		jucator.start_game();//nu stiu daca tre sa fac bool si dupa apelez functia
	}
	get_user.set_standard_input(false);
	system("cls");
	user(30, 75) << "User not found.Returning to main menu ";
	Sleep(5000);
	Main_menu meniu;
	meniu.draw();
}




void IntroJoc::Runjoc()
{
	
	UserInterface::IntroOUT conOut = UserInterface::IntroOUT::getInstance();
	UserInterface::IntroIN conIn = UserInterface::IntroIN::getInstance();
	Main_menu meniu;
	meniu.draw();
	while (true)
	{
		std::string action = conIn.getUserActions();
		/*if (action != "")
		{
			conOut(41, 2) << action;
		}*/
		 if (action == "1")
		{
			create_new_user();
			break;
		}
		else if (action == "2")
		{
			 //if (change_user())//or asa pt bool
			 change_user();
			break;
		}
		else if (action == "3")
		{
			exit(0);
		}
	}


}

void IntroJoc::play()
{
	Player jucator;
	jucator.start_game();//tre sa dau pun parametru nume,level ..)
}

IntroJoc::IntroJoc()
{
}


IntroJoc::~IntroJoc()
{
}
