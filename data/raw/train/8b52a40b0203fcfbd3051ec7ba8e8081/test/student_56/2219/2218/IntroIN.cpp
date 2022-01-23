#include <stdio.h>
#include <windows.h>
#include "IntroIN.h"
#include <string>

using namespace UserInterface;

void ExceptionHandler1(const char *s)
{
	// TODO: you should handle this
	exit(1);
}

IntroIN::IntroIN()
{
	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ExceptionHandler1("GetStdHandle");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ExceptionHandler1("GetConsoleMode");

	// Disable 'Quick Edit Mode' option.
	fdwMode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hStdin, fdwMode))
		ExceptionHandler1("SetConsoleMode");
	
	// Enable the window and mouse input events.
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ExceptionHandler1("SetConsoleMode");
}

IntroIN::~IntroIN()
{
}

void IntroIN::set_standard_input(bool standard)
{
	if (standard == 1)
		SetConsoleMode(hStdin, fdwSaveOldMode);
	else
	{
		// Disable 'Quick Edit Mode' option.
		fdwMode = ENABLE_EXTENDED_FLAGS;
		if (!SetConsoleMode(hStdin, fdwMode))
			ExceptionHandler1("SetConsoleMode");

		// Enable the window and mouse input events.
		fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
		if (!SetConsoleMode(hStdin, fdwMode))
			ExceptionHandler1("SetConsoleMode");
	}

}

IntroIN & UserInterface::IntroIN::getInstance(void)
{
	// TODO: singleton logics
	IntroIN *console = new IntroIN();
	return *console;
}

std::string IntroIN::mouseEventProc(MOUSE_EVENT_RECORD ir)
{
	std::string output = "Mouse event: ";
	switch (ir.dwEventFlags)
	{
	case MOUSE_MOVED:
		output += "moved(";
		output += std::to_string(ir.dwMousePosition.X);
		output += ", ";
		output += std::to_string(ir.dwMousePosition.Y);
		output += ")              ";
		return output;

	case DOUBLE_CLICK:
		output += "dc(";
		output += std::to_string(ir.dwMousePosition.X);
		output += ", ";
		output += std::to_string(ir.dwMousePosition.Y);
		output += ")              ";
		return output;
	}
	return output;
}
std::string IntroIN::resizeEventProc(WINDOW_BUFFER_SIZE_RECORD) { return ""; };
std::string IntroIN::keyEventProc(KEY_EVENT_RECORD event) 
{
	char nume = event.uChar.AsciiChar;//am parcurs structura in debuger pt a primi codul ascii al tastei apasate
	std::string to_ret;
	to_ret.push_back(nume);
	return to_ret;//returneaza caracterul
	//return ""; 
};

std::string UserInterface::IntroIN::getUserActions()
{
	DWORD nr = 0;
	GetNumberOfConsoleInputEvents(hStdin, &nr);
	if (nr)
	{
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ExceptionHandler1("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				return keyEventProc(irInBuf[i].Event.KeyEvent);

			case MOUSE_EVENT: // mouse input 
				return mouseEventProc(irInBuf[i].Event.MouseEvent);

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				return resizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);

			case FOCUS_EVENT:  // disregard focus events 
				return "";

			case MENU_EVENT:   // disregard menu events 
				return "";

			default:
				ExceptionHandler1("unknown event type");
				break;
			}
		}
	}
	
	return "";
}