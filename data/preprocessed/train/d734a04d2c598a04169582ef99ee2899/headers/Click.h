#pragma once
#include "ConsoleOutput.h"
#include "ConsoleInput.h"
#include "SunField.h"
#include "BattleField.h"
#include "ExceptionHandler.h"

class Click
{
private:
	int sun_value = 0;
public:
	Click();
	~Click();
	void get_click(int x, int y);
	void click_sun(int poz);
	void click_plant(int nr);
	void put_plant(int plant_id);


};

