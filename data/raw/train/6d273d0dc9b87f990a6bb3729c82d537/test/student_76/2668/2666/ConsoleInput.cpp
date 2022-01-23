#include <stdio.h>
#include <windows.h>
#include "ConsoleInput.h"
#include <string>
#include "CExceptii.h"
using namespace UserInterface;
ConsoleInput* ConsoleInput::instance = nullptr;

ConsoleInput::ConsoleInput()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
	{
		throw new CExceptii("GetStdHandle",0);
	}
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		throw new CExceptii("GetConsoleMode",0);	
}

ConsoleInput::~ConsoleInput()
{
}

void UserInterface::ConsoleInput::RemoveInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance == nullptr;
	}
}

ConsoleInput& UserInterface::ConsoleInput::getInstance(void)
{
	if (instance == nullptr)
	{
		instance = new ConsoleInput();
	}
	return *instance;
}

std::string ConsoleInput::mouseEventProc(MOUSE_EVENT_RECORD ir, CPoint& Point)
{
	std::string output;
	Point.SetX(ir.dwMousePosition.Y);
	Point.SetY(ir.dwMousePosition.X);
	switch (ir.dwEventFlags)
	{
	case MOUSE_MOVED:
		output = "move";
		return output;

	case DOUBLE_CLICK:
		output = "double click";
		return output;
	}
	return output;
}
std::string ConsoleInput::resizeEventProc(WINDOW_BUFFER_SIZE_RECORD) { return ""; };
std::string ConsoleInput::keyEventProc(KEY_EVENT_RECORD) { return ""; };

std::string UserInterface::ConsoleInput::getUserActions(CPoint& Point)
{
	DWORD nr = 0;
	GetNumberOfConsoleInputEvents(hStdin, &nr);
	if (nr)
	{
		if (!ReadConsoleInput(
			hStdin,     
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			throw new CExceptii("ReadConsoleInput",1);

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: 
				return keyEventProc(irInBuf[i].Event.KeyEvent);

			case MOUSE_EVENT: 
				return mouseEventProc(irInBuf[i].Event.MouseEvent,Point);

			case WINDOW_BUFFER_SIZE_EVENT: 
				return resizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);

			case FOCUS_EVENT:   
				return "";

			case MENU_EVENT:   
				return "";

			default:
				throw new CExceptii("unknown event type",0);
				break;
			}
		}
	}

	return "";
}

void UserInterface::ConsoleInput::ResetFlags()
{
	SetConsoleMode(hStdin, fdwSaveOldMode);
}

void UserInterface::ConsoleInput::SetFlags()
{
	fdwMode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hStdin, fdwMode))
		throw new CExceptii("SetConsoleMode", 0);

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		throw new CExceptii("SetConsoleMode", 0);
}
