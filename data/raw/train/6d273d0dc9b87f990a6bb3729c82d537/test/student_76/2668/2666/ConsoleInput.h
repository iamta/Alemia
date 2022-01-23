#pragma once
#include <windows.h>
#include <string>
#include "CPoint.h"
namespace UserInterface
{
	class ConsoleInput
	{
	private:
		HANDLE hStdin;
		DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
		INPUT_RECORD irInBuf[128];
		std::string mouseEventProc(MOUSE_EVENT_RECORD, CPoint& Point);
		std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
		std::string keyEventProc(KEY_EVENT_RECORD);
		ConsoleInput();
		~ConsoleInput();
		static ConsoleInput* instance;
	public:
		static void RemoveInstance();
		static ConsoleInput& getInstance(void);
		std::string getUserActions(CPoint&Point);
		void ResetFlags();
		void SetFlags();
	};
}


