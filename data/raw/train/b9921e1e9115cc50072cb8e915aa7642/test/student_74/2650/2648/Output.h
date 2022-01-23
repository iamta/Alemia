#pragma once
#include<Windows.h>
#include<iostream>
class Output
{
	static Output* console;
	HANDLE handle, hNewScreenBuffer;
	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	static CHAR_INFO chiBuffer[5106];
	COORD coordBufSize;
	COORD coordBufCoord;
	Output() { consoleInit(); }
public:
	static Output& getInstance();
	void consoleInit(COORD windowSize = { 1280, 720 });
	void consoleUpdate(int pozX, int pozY, std::pair<std::string, unsigned char> obj)
	{
		int p = pozY * 138 + pozX;
		if (p < 5106) {
			for (auto i = 0; i < obj.first.size(); i++)
			{
				chiBuffer[p+i].Char.AsciiChar = obj.first[i];
				chiBuffer[p+i].Attributes = obj.second;
			}
		}
	}
	void consolePrint() {
		WriteConsoleOutput(hNewScreenBuffer,chiBuffer,coordBufSize,coordBufCoord,&srctWriteRect);
	}
	void consoleClear() {
		for (int i = 0; i < 37; i++)
		{
			for (int j = 0; j < 138; j++)
			{
				chiBuffer[i * 138 + j].Char.UnicodeChar = 32;
				chiBuffer[i * 138 + j].Attributes = 15;
			}
		}
	}
};