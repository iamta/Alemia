#pragma once
#include <windows.h>
#include "UserAction.h"
#include <string>
/*TODO: singleton*/
namespace UserInterface
{
	class ConsoleInput
	{
	private:
		HANDLE hStdin;
		DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
		INPUT_RECORD irInBuf[128];
		UserAction mouseEventProc(MOUSE_EVENT_RECORD);
		std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
		std::string keyEventProc(KEY_EVENT_RECORD);

	public:
		ConsoleInput();
		~ConsoleInput();

		static ConsoleInput & getInstance(void);
		UserAction getUserActions();
	};
}


