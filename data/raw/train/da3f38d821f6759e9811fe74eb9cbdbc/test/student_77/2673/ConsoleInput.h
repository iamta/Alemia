#pragma once
#include <windows.h>
#include <string>
namespace UserInterface
{
	class ConsoleInput
	{
	private:
		HANDLE hStdin;
		DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
		INPUT_RECORD irInBuf[128];
		std::string mouseEventProc(MOUSE_EVENT_RECORD,int *&);
		std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
		std::string keyEventProc(KEY_EVENT_RECORD);

		ConsoleInput();
		static ConsoleInput *console;

	public:


		static ConsoleInput & getInstance();
		std::string getUserActions(int *&);

	};
}
