#pragma once

#include <windows.h>
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
		std::string mouseEventProc(MOUSE_EVENT_RECORD);
		std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
		std::string keyEventProc(KEY_EVENT_RECORD);

		int x;
		int y;

		static ConsoleInput* pInstance;
		ConsoleInput();

	public:

		~ConsoleInput();

		int getX() { return x; }
		int getY() { return y; }
		void setX(int a) { x = a; }
		void setY(int b) { y = b; }

		static ConsoleInput & getInstance(void);
		std::string getUserActions();
	};
}


