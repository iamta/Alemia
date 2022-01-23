#include "Engine.h"
#include "Menu.h"
int main() {

	Engine e(Menu::show_select());
	while (e.run());
	Menu::game_over();
	return 0;
}