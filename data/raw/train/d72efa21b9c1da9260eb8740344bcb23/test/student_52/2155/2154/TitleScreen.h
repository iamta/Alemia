#pragma once
#include<iostream>
class TitleScreen
{

private:

	static TitleScreen* instance;

	TitleScreen() {};
	TitleScreen(const TitleScreen&) {};
	~TitleScreen() {};

	std::string username;
	std::string password;

public:

	static TitleScreen* getInstance();
	static void DestroyInstance();


	void DisplayTitleScreen();
	
	
	void getLogs();
	

};

