#pragma once
#include <windows.h>
#include <string>
/*TODO: singleton*/
namespace UserInterface
{
	class IntroIN
	{
	private:
		HANDLE hStdin;
		DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
		INPUT_RECORD irInBuf[128];
		std::string mouseEventProc(MOUSE_EVENT_RECORD);
		std::string resizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
		std::string keyEventProc(KEY_EVENT_RECORD);

	public:
		IntroIN();
		~IntroIN();

		static IntroIN & getInstance(void);
		std::string getUserActions();//asta intoarce string cand se apasa orice tasta

		void set_standard_input(bool standard);

	};
}


