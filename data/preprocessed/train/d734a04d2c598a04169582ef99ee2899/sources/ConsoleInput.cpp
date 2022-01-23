#include "ConsoleInput.h"
#include "ExceptionHandler.h"

using namespace UserInterface;

ConsoleInput* ConsoleInput::instance = nullptr;

ConsoleInput::ConsoleInput()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ExceptionHandler("GetStdHandle INVALID_HANDLE_VALUE");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ExceptionHandler("GetConsoleMode failed");

	// Disable 'Quick Edit Mode' option.
	fdwMode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hStdin, fdwMode))
		ExceptionHandler("SetConsoleMode failed");

	// Enable the window and mouse input events.
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ExceptionHandler("SetConsoleMode_2 failed");
}


ConsoleInput::~ConsoleInput()
{
}

ConsoleInput& UserInterface::ConsoleInput::getInstance()
{
	if (instance == nullptr)
		instance = new ConsoleInput;

	return *instance;
}

std::string ConsoleInput::mouseEventProc(MOUSE_EVENT_RECORD ir)
{
	std::string output = "Mouse event: ";
	switch (ir.dwEventFlags)
	{
	case MOUSE_MOVED:
		output += "mouse moved at (";
		output += std::to_string(ir.dwMousePosition.X);
		output += ", ";
		output += std::to_string(ir.dwMousePosition.Y);
		output += ")              ";
		return output;
		//return "";

	case DOUBLE_CLICK:
		output += "mouse double clicked at (";
		output += std::to_string(ir.dwMousePosition.X);
		output += ", ";
		output += std::to_string(ir.dwMousePosition.Y);
		output += ")              ";
		return output;
	}

	switch (ir.dwButtonState)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:
		this->x_coord = ir.dwMousePosition.X;
		this->y_coord = ir.dwMousePosition.Y;

		output += "mouse clicked at (";
		output += std::to_string(ir.dwMousePosition.X);
		output += ", ";
		output += std::to_string(ir.dwMousePosition.Y);
		output += ")              ";
		return output;
	}
	return output;
}

std::string ConsoleInput::keyEventProc(KEY_EVENT_RECORD kr) {
	static std::string output = "";

	if (kr.bKeyDown) {
		if (kr.uChar.AsciiChar == '\r') {
			output = "";
			return "exit";
		}
		else
			return output += kr.uChar.AsciiChar;
	}

	return "";
}
std::string UserInterface::ConsoleInput::getUserActions()
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
			ExceptionHandler("ReadConsoleInput failed");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				return keyEventProc(irInBuf[i].Event.KeyEvent);

			case MOUSE_EVENT: // mouse input 
				return mouseEventProc(irInBuf[i].Event.MouseEvent);

				//case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				//	return resizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);

			case FOCUS_EVENT:  // disregard focus events 
				return "";

			case MENU_EVENT:   // disregard menu events 
				return "";

			default:
				ExceptionHandler("unknown event type");
				break;
			}
		}
	}

	return "";
}