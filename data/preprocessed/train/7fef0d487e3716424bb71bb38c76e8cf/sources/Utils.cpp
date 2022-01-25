#include "Utils.h"
#include "ConsoleOutput.h"


int Utils::BCX_Line_Console(int x1, int y1, int x2, int  y2)
{
    auto instance = UserInterface::ConsoleOutput::getInstance();
    x1 = x1 / 20;
    x2 = x2 / 20;
    y1 = y1 / 10;
    y2 = y2 / 10;

    if (y1 == y2)
    {
        // Horizontal line
        auto _min = min(x1, x2);
        auto _max = max(x1, x2);
        for (int i = _min + 1; i < _max; i++)
            instance(i, y1) << '-';
    }
    if (x1 == x2)
    {
        //Vertical Line
        auto _min = min(y1, y2);
        auto _max = max(y1, y2);
        for (int i = _min + 1; i < _max; i++)
            instance(x1, i) << '-';
    }
    // Not supported other types of lines
    return 0;
}

int Utils::BCX_Rectangle_Console(int x1, int y1, int x2, int y2, bool Fill)
{
    auto instance = UserInterface::ConsoleOutput::getInstance();
    // draw  ---
    BCX_Line_Console(x1, y1+1, x1,y2);
    //draw |
    BCX_Line_Console(x1, y2, x2, y2);

    //draw ---
    BCX_Line_Console(x2, y2, x2, y1);

    //draw ---
    BCX_Line_Console(x1, y1, x2, y1);

    x1 = x1 / 20;
    x2 = x2 / 20;
    y1 = y1 / 10;
    y2 = y2 / 10;

    if (Fill == true)
    {
        auto _min_x = min(x1, x2);
        auto _max_x = max(x1, x2);

        auto _min_y = min(y1, y1);
        auto _max_y = max(y2, y2);

        for (auto i = x1 + 1; i < x2; i++)
        {
            for (auto j = y1 + 2; j < y2 - 1; j++)
            {
                instance(i, j) << "-";
            }
        }
    }
    return 0;
}

int Utils::BCX_DrawNumber_Console(int X, int Y, string Number)
{
    X = X / 20;
    Y = Y / 10;
    UserInterface::ConsoleOutput::Refresh();
    auto instance = UserInterface::ConsoleOutput::getInstance();
    instance(X,Y) << Number;
    return 0;
}

int Utils::BCX_Clear(int x1, int y1, int x2, int y2)
{
    auto instance = UserInterface::ConsoleOutput::getInstance();
    x1 = x1 / 20;
    x2 = x2 / 20;
    y1 = y1 / 10;
    y2 = y2 / 10;
    auto _min_x = min(x1, x2);
    auto _max_x = max(x1, x2);

    auto _min_y = min(y1, y1);
    auto _max_y = max(y2, y2);

    for (auto i = x1 + 1; i < x2; i++)
    {
        for (auto j = y1 + 2; j < y2 - 1; j++)
        {
            instance(i, j) << " ";
        }
    }
    return 0;
}