#pragma once
#include"Output.h"
#include"Input.h"
class Menu
{
public:
	static int show_select() {
		Output cout = Output::getInstance();
		Input mouse = Input::getInstance();
		cout.consoleUpdate(61, 16, { ">> Play (1) <<", 240 });
		cout.consoleUpdate(61, 17, { ">> Play (2) <<", 240 });
		cout.consoleUpdate(61, 18, { ">> Play (3) <<", 240 });
		cout.consoleUpdate(61, 19, { ">>   Exit   <<", 240 });
		cout.consolePrint();
		while (true) {
			if (mouse.get_mouse_state().second == 1) {
				if (mouse.get_mouse_state().first.Y == 16 && mouse.get_mouse_state().first.X >= 61 && mouse.get_mouse_state().first.X <= 61 + 15)
					return 1;
				if (mouse.get_mouse_state().first.Y == 17 && mouse.get_mouse_state().first.X >= 61 && mouse.get_mouse_state().first.X <= 61 + 15)
					return 2;
				if (mouse.get_mouse_state().first.Y == 18 && mouse.get_mouse_state().first.X >= 61 && mouse.get_mouse_state().first.X <= 61 + 15)
					return 3;
				if (mouse.get_mouse_state().first.Y == 19 && mouse.get_mouse_state().first.X >= 61 && mouse.get_mouse_state().first.X <= 61 + 15)
					exit(0);
			}
		}
	}
	static void game_over() {
		Output cout = Output::getInstance();
		Input mouse = Input::getInstance();
		cout.consoleClear();
		cout.consoleUpdate(61, 19, { ">>   Game Over   <<", 240 });
		cout.consolePrint();
		Sleep(5000);
	}
};

