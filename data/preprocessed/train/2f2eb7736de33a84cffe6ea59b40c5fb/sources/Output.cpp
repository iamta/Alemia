#include "Output.h"
Output* Output::console = nullptr;
CHAR_INFO Output::chiBuffer[5106];
Output& Output::getInstance()
{
	if (console == nullptr)
		console = new Output();
	return *console;
}

void Output::consoleInit(COORD windowSize)
{
	HWND console = GetConsoleWindow();
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	hNewScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);
	if (handle == INVALID_HANDLE_VALUE ||
		hNewScreenBuffer == INVALID_HANDLE_VALUE)
	{
		printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
		return;
	}
	if (!SetConsoleActiveScreenBuffer(hNewScreenBuffer))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		return;
	}

	//Set characters size (i did't make them square by default, pixels)
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = windowSize.X / 138;
	cfi.dwFontSize.Y = windowSize.Y / 37;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	if (!SetCurrentConsoleFontEx(hNewScreenBuffer, false, &cfi));
	//error
	
	srctReadRect.Top = 0;
	srctReadRect.Left = 0;
	srctReadRect.Bottom = 36;
	srctReadRect.Right = 137;


	coordBufSize.Y = 37;
	coordBufSize.X = 138;

	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;

	srctWriteRect.Top = 0;
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = 36;
	srctWriteRect.Right = 137;

	RECT r;
	GetWindowRect(console, &r);

	//Set console title(just to be fancy)
	SetConsoleTitle("Plants vs Zombies");

	// Setting console width and height
	MoveWindow(console, 0, 0, windowSize.X, windowSize.Y, TRUE);

	//Disable Window Resize
	SetWindowLong(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);

	// Hiding scrollbar
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};	//  #error_size_too_small
	SetConsoleScreenBufferSize(handle, new_size);

	// Disable 'Quick Edit Mode' option.
	DWORD fdwMode = ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwMode);

	// Enable the window and mouse input events.
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwMode);

	// Hide blinking cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(handle, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(handle, &cursorInfo);

}

