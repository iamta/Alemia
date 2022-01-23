#pragma once
# include <iostream>
# include <string>
# include <Windows.h>
# include "Entity.h"
# include "Plant.h"
# include "PlantList.h"
# include "SunList.h"
# include "Money.h"
# include "Grid.h"
# include "Bullet.h"
# include "Bullet_normal.h"
# include "Bullet_frozen.h"
# include "BulletList.h"
# include "Logfile.h"
class Input
{
	HANDLE hStdin;
	DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
	INPUT_RECORD irInBuf[128];
	COORD mouse_pos;
	 static Entity * temp;
	 static Bullet * TempBul;
	 int isSelected = 0;
	 int hold;

public:
	Input();
	void print_mouse();
	COORD get_mouse_cord() { return mouse_pos; }
	
	DWORD get_mouse_botton_state(MOUSE_EVENT_RECORD ir);
	bool select(PlantList &e,SunList &Floare,Money&money,BulletList &gloante, Logfile&L);
	void deselect(Grid&G,PlantList &e,BulletList&B, Logfile&L);
	void check_if_sunflower(int i, SunList&Floare);
	bool snap_tool_grid(Grid & G,PlantList&e);
	
	virtual~Input();
};