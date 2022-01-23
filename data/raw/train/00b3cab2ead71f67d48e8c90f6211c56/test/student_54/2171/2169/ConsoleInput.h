#pragma once
#include <windows.h>
#include <string>

class ConsoleInput
{
private:
	HANDLE hStdin;
	DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
	INPUT_RECORD irInBuf[128];
	std::string mouseEventProc(MOUSE_EVENT_RECORD);
	std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
	std::string keyEventProc(KEY_EVENT_RECORD);
	ConsoleInput();
	~ConsoleInput();
	static ConsoleInput*instance;

public:
	static void destroyInstance();
	static ConsoleInput & getInstance();
	std::string getUserActions();
};

