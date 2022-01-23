#pragma once
#include <windows.h>
#include <string>
/*TODO: singleton*/
namespace UserInterface
{
	typedef struct x_y
	{
		int x = 0;
		int y = 0;

	};

	class ConsoleInput
	{
	private:
		HANDLE hStdin;
		DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
		INPUT_RECORD irInBuf[128];
		std::string mouseEventProc(MOUSE_EVENT_RECORD);
		std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
		std::string keyEventProc(KEY_EVENT_RECORD);
		
	public:
		ConsoleInput();
		~ConsoleInput();
		x_y coord;
		static ConsoleInput & getInstance(void);
		std::string getUserActions();
	};
}


