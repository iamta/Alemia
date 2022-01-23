#pragma once
#include <windows.h>    // Win32API Header File
#include <cstring>
#include <cstdio>
#include <string>
#include <cstdio>
using namespace std;

//
//#define Red  RGB (255,0,0)
//#define Lime RGB (206,255,0)
//#define Blue RGB (0,0,255)
//#define Green RGB (0,255,255)
//#define Yellow RGB (0,255,150)
//
//
class Utils
{
public:
    static const int SUN_START_HEADERS = 200;
    static const int SUN_HEADER_HEIGHT = 100;
    static const int SUN_SQUARE_DIM = 120;
    static const int SUN_NUM_SLOTS = 8;
    static const int PLANTS_NUM_SLOTS = 6;
    static const int PLANT_SQUARE_DIM = SUN_SQUARE_DIM;
    static const int SCOREBOARD_HEIGHT = 100;
    static const int SCOREBOARD_WIDTH = 100;
    static const int THREESHOLD_BETWEEN_SQUARES = 10;
    static const int THREESHOLD_BETWEEN_COMPONENTS = 20;

    // Constants logic
    static const int THREESHOLD_SPEED_MOVING = 200;

   static int BCX_Line_Console(int x1, int y1, int x2, int y2);
    static int BCX_Rectangle_Console(int x1, int y1, int x2, int y2, bool Fill = false);
    static int BCX_DrawNumber_Console(int X, int Y, string Number);

    static int BCX_Clear(int x1, int y1, int x2, int y2);
};

