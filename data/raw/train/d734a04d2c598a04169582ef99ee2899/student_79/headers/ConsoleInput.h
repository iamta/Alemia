#pragma once
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>


namespace UserInterface {

	class ConsoleInput
	{
	private:
		static ConsoleInput* instance;
		HANDLE hStdin;
		DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
		INPUT_RECORD irInBuf[128];
		std::string mouseEventProc(MOUSE_EVENT_RECORD);
		//std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
		std::string keyEventProc(KEY_EVENT_RECORD);

		int x_coord;
		int y_coord;

	public:
		ConsoleInput();
		~ConsoleInput();

		static ConsoleInput& getInstance();
		std::string getUserActions();

		int get_x() { return x_coord; };
		int get_y() { return y_coord; };
	};
}

