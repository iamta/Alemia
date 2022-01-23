#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
class Input
{
	DWORD cNumRead;
	INPUT_RECORD irInBuf[128];
	static Input* console;
	std::pair<COORD, short> mouse;
	Input() {}
public:
	std::pair<COORD, short>& get_mouse_state();
	static Input& getInstance();
};

