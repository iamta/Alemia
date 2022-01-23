#include "Input.h"
Input* Input::console = nullptr;

std::pair<COORD, short>& Input::get_mouse_state()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	DWORD nr = 0;
	GetNumberOfConsoleInputEvents(hIn, &nr);
	if (nr)
	{
		if (ReadConsoleInput(hIn, irInBuf, 128, &cNumRead)) {
			for (auto i = 0; i < cNumRead; i++) {
				if (irInBuf[i].EventType == MOUSE_EVENT) {

					if (irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
						mouse.second = 1;
					else if (irInBuf[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
						mouse.second = 2;
					else mouse.second = 0;
					mouse.first = { irInBuf[i].Event.MouseEvent.dwMousePosition.X , irInBuf[i].Event.MouseEvent.dwMousePosition.Y };
				}
			}
		}
	}
	return mouse;
}
	Input& Input::getInstance()
	{
		if (console == nullptr)
			console = new Input();
		return *console;
	}
