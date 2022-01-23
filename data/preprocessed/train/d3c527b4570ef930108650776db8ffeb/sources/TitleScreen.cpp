#define _CRT_SECURE_NO_WARNINGS
#include "TitleScreen.h"
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<cwchar>
#include"graphics.h"
#include<stdio.h>
#include<dos.h>
#include<fstream>


using namespace std;

TitleScreen* TitleScreen::instance = nullptr;

TitleScreen* TitleScreen::getInstance()
{
	if (!TitleScreen::instance)
	{
		TitleScreen::instance = new TitleScreen();
	}

	return instance;
}

void TitleScreen::DestroyInstance()
{
	if (TitleScreen::instance)
	{
		delete TitleScreen::instance;
		TitleScreen::instance = nullptr;
	}
}

void TitleScreen::DisplayTitleScreen()
{

	

	//CONSOLE_FONT_INFOEX cfi;
	//cfi.cbSize = sizeof(cfi);
	//cfi.nFont = 0;
	//cfi.dwFontSize.X = 0;                   // Width of each character in the font
	//cfi.dwFontSize.Y = 44;                  // Height
	//cfi.FontFamily = FF_DONTCARE;
	//cfi.FontWeight = FW_NORMAL;
	//std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	////Get the window console handle(isn't the right code but works for these sample
	//HWND ConsoleWindow;
	//ConsoleWindow = GetForegroundWindow();

	////Getting the desktop hadle and rectangule
	//HWND   hwndScreen;
	//RECT   rectScreen;
	//hwndScreen = GetDesktopWindow();
	//GetWindowRect(hwndScreen, &rectScreen);

	////Set windows size(see the width problem)
	//SetWindowPos(ConsoleWindow, NULL, 0, 0, 600, 600, SWP_SHOWWINDOW);

	//// Get the current width and height of the console
	//RECT rConsole;
	//GetWindowRect(ConsoleWindow, &rConsole);
	//int Width = rConsole.left = rConsole.right;
	//int Height = rConsole.bottom - rConsole.top;

	////caculate the window console to center of the screen	
	//int ConsolePosX;
	//int ConsolePosY;
	//ConsolePosX = ((rectScreen.right - rectScreen.left) / 2 - Width / 2);
	//ConsolePosY = ((rectScreen.bottom - rectScreen.top) / 2 - Height / 2);
	//SetWindowPos(ConsoleWindow, NULL, ConsolePosX, ConsolePosY, Width, Height, SWP_SHOWWINDOW || SWP_NOSIZE);


	HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "\n\n\n";
	cout << "     ";

    SetConsoleTextAttribute(m_hConsole,
        FOREGROUND_RED |
        FOREGROUND_INTENSITY |
        BACKGROUND_GREEN |
        BACKGROUND_INTENSITY);

	
    std::cout << "Plants vs Zombie";

	
	

	

	



    SetConsoleTextAttribute(m_hConsole,
        FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE);

	cout << "\n\n\n";

	

	

	
}

void TitleScreen::getLogs()
{
	string usern;
	string pass;

	cout << "Username: ";
	cin >> usern;
	cout << "Password: ";
	cin >> pass;


	ifstream outfile;
	outfile.open("logs_database.txt");

	string buffer;
	string fileContent;
	int level = 0;

	int lineCounter = 0;

	bool addToLogs = 0;
	bool wrongPass = 0;

	if (outfile.is_open())
	{
		while (!outfile.eof())
		{
			getline(outfile, buffer);
			lineCounter++;
		}
	}

	outfile.close();
	outfile.open("logs_database.txt");
	
	int counter=0;

	if (outfile.is_open())
	{
		while (!outfile.eof())
		{
			getline(outfile, buffer);
			counter++;
			if ((counter)%3==2 && buffer==usern)
			{
				addToLogs = 1;
			}
			if (counter == lineCounter)
			{
				fileContent = fileContent + buffer;
			}
			else
			{
				fileContent = fileContent + buffer + "\n";
			}
			
		}
	}

	outfile.close();
	outfile.open("logs_database.txt");

	

	bool SearchUser = 0;
	int new_counter = 1;

	if (outfile.is_open())
	{
		while (!outfile.eof())
		{

			getline(outfile, buffer);
		
			if (SearchUser == 1)
			{
				if (buffer!=pass)
				{
					cout << endl;
					cout << "  Wrong Password!\n";
					cout << "  The game will now close.";
					cout << "\n\n\n";
					exit(EXIT_FAILURE);
					break;
					
				}
				else
				{
					break;
				}
			}

			if ((new_counter ) % 3 == 2 && buffer == usern)
			{
				SearchUser = 1;
			}
			
			new_counter++;
		}
	}

	outfile.close();

	ofstream outfile2("logs_database.txt");

	if (fileContent == "\n")
	{
		outfile2 <<usern + "\n" + pass +"\n" + to_string(level);
	}

	if (addToLogs==0&&fileContent!="\n")
	{
		outfile2 << fileContent + "\n" + usern + "\n" + pass + "\n" + to_string(level);
	}

	if (addToLogs == 1 && fileContent != "\n")
	{
		outfile2 << fileContent;
	}



	Sleep(2000);

	cout << flush;
	system("CLS");
}