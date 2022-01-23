#define _CRT_SECURE_NO_WARNINGS
#include "LoadingScreen.h"
#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include<cwchar>
#include"graphics.h"

#include<stdio.h>
#include<dos.h>


using namespace std;

LoadingScreen* LoadingScreen::instance = nullptr;

LoadingScreen* LoadingScreen::getInstance()
{
	if (!LoadingScreen::instance)
	{
		LoadingScreen::instance = new LoadingScreen();
	}

    return instance;
}

void LoadingScreen::DestroyInstance()
{
	if (LoadingScreen::instance)
	{
		delete LoadingScreen::instance;
		LoadingScreen::instance = nullptr;
	}
}

void LoadingScreen::DisplayLoadingScreen()
{
    
    initgraph();
    

    

    


    for (int i = 0; i < 10; i++)
    {
        cout << endl;
    }

    int x1, y1;
    x1 = 50;
    y1 = 100;

    int line1X1 = 150;
    int line1Y1 = 150;
    int line2X1 = 300;
    int line2Y1  =300;

   

    for (int i=0;i<=9;i++) {

        setfontcolor(i+1);
        setcolor(i+1);
       
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b Loading  " << std::flush;
        Sleep(this->minDelay);

        
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b LOading   " << std::flush;
        Sleep(this->minDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b LoAding   " << std::flush;
        Sleep(this->minDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b LoaDing   " << std::flush;
        Sleep(this->minDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b LoadIng   " << std::flush;
        Sleep(this->minDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b LoadiNg   " << std::flush;
        Sleep(this->minDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b LoadinG   " << std::flush;
        Sleep(this->minDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b Loading.  " << std::flush;
        Sleep(this->maxDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b Loading.." << std::flush;
        Sleep(this->maxDelay);
        std::cout << "\b\b\b\b\b\b\b\b\b\b\b Loading..." << std::flush;
        Sleep(this->maxDelay);

        line(0, line1X1, 10000, line1Y1);

        line1X1 -= 5;
        line1Y1 -= 5;
        line2X1 += 5;
        line2Y1 += 5;
        line(0, line2X1, 10000, line2Y1);

        /*rectangle(50, 50, 100, 100);
        rectangle(150,50, 200, 100);
        rectangle(250, 50, 300, 100);*/

        rectangle(x1, 15, y1, 65);
        
        rectangle(x1, 400, y1, 450);
        
        
        x1 += 100;
        y1 += 100;
        
    }

    cout << "\n\n\t\t\t\t\t\t Powered by Alex Olaru";

    Sleep(5000);

    

    cout << flush;
    system("CLS");

    
    
}