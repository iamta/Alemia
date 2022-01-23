#pragma once

class LoadingScreen
{
private:
	
	int minDelay = 50;
	int maxDelay = 50;

	static LoadingScreen* instance;

	LoadingScreen() {};
	LoadingScreen(const LoadingScreen&) {};
	~LoadingScreen() {};

public:

	static LoadingScreen* getInstance();
	static void DestroyInstance();
	

	void DisplayLoadingScreen();

	
};

