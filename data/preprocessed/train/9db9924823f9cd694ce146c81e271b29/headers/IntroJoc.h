#pragma once
#include <string>
class IntroJoc
{
private:
	const int ROW_TITLE= 20;
	const int COL_FIRST_STAR_POSITION = 75;
	const int COL_DISTANCE_BETWEEN_STARS = 5;
	std::string nume_player;
private:
	void doLoadingBar();
	void create_new_user();
	void change_user();
public:
	void LoadingScreen();
	void Runjoc();
	void play();
	IntroJoc();
	~IntroJoc();
};

