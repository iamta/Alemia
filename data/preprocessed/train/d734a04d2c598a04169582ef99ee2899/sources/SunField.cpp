#include "SunField.h"

SunField* SunField::instance = nullptr;


SunField* SunField::GetInstance()
{
	if (instance == nullptr)
		instance = new SunField;

	return instance;
}

SunField::SunField()
{
	sun_array.fill(0);
}


SunField::~SunField()
{
}

const void SunField::print_field() const
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	
	for (int i = 2; i < 6; i++)
	{
		conOut(i, 16) << char(179);
		conOut(i, 29) << char(179);
	}
	for (int i = 16; i < 29; i++)
	{
		conOut(6, i) << char(196);
		conOut(1, i) << char(196);
	}

	for (int i = 40; i < 96; i++) {
		conOut(1, i) << char(196);
		conOut(6, i) << char(196);
	}
	for (int i = 40; i <= 96; i += 7) {
		for (int j = 2; j < 6; j++) {
			conOut(j, i) << char(179);
		}
	}

}

void SunField::print_sun(int pos)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED |
		BACKGROUND_GREEN | BACKGROUND_RED);
	sun_array[pos - 1] = 1;
	switch (pos)
	{
	case 1:
		conOut(4, 43) << "**";
		conOut(5, 43) << "**";
		break;
	case 2:
		conOut(4, 50) << "**";
		conOut(5, 50) << "**";
		break;
	case 3:
		conOut(4, 57) << "**";
		conOut(5, 57) << "**";
		break;
	case 4:
		conOut(4, 64) << "**";
		conOut(5, 64) << "**";
		break;
	case 5:
		conOut(4, 71) << "**";
		conOut(5, 71) << "**";
		break;
	case 6:
		conOut(4, 78) << "**";
		conOut(5, 78) << "**";
		break;
	case 7:
		conOut(4, 85) << "**";
		conOut(5, 85) << "**";
		break;
	case 8:
		conOut(4, 92) << "**";
		conOut(5, 92) << "**";
		break;
	default:
		break;
	}
}

