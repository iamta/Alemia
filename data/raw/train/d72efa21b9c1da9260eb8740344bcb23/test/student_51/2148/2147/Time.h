#pragma once
#include <time.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
class timer {
private:
	unsigned long begTime;
public:
	void start() {
		begTime = clock();
	}

	unsigned long elapsedTime() {
		return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	}

	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	}

	unsigned long Mili()
	{
		unsigned long a;
		
		return a=((((((unsigned long)clock() - begTime) / (CLOCKS_PER_SEC/1000))/100)%10));

	}
	void Ttimer();

};