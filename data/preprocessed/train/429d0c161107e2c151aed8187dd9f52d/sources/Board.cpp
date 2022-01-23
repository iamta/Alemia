#include "Board.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include "graphics.h"
#include<time.h>


#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

using namespace std;

Board* Board::instance = nullptr;


Board *Board::getInstance()
{
	if (!Board::instance)
	{
		Board::instance = new Board();
	}

	return instance;
}

void Board::DestroyInstance()
{
	if (Board::instance)
	{
		delete Board::instance;
		Board::instance = nullptr;
	}
}
void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Board::PrintBoard()
{
	
    /*ClearScreen();*/

    cout << string(10, '\n');

	cout << "  SCORE: " << score << endl;
	cout << "  RESOURCES: " << money << endl;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 55; j++)
		{
			cout << matrix[i][j];
		}
		cout << endl;
	}
   
}

void Board::renewSun(int pos)
{
    int theJpos;
    int currentPos = 10;
    int contor = 1;
    
    for (int i = 10; i < 50; i += 3)
    {
        if (contor==pos)
        {
            theJpos = i;
            break;
        }
        else
        {
            contor++;
        }
    }

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 55; j++)
        {
            if ((i == 1 || i == 2) && (j == theJpos || j == theJpos + 1))
            {
                matrix[i][j] = "S ";
            }
        }
        
    }
}

int Board::clickSun(int pos)
{
    int searchPos = 20;
    int sunNumber = -999;

    for (int i = 0; i < 9; i++)
    {
        if (pos==searchPos||pos==searchPos+1||pos==searchPos+2)
        {
            sunNumber = i;
            break;
        }
        else
        {
            searchPos += 6;
        }
    }
    cout << sunNumber;
    return sunNumber +1;
    
}

void Board::collectSun(int pos)
{
    int theJpos = -9;
    int currentPos = 10;
    int contor = 1;

    for (int i = 10; i < 50; i += 3)
    {
        if (contor == pos)
        {
            theJpos = i;
            break;
        }
        else
        {
            contor++;
        }
    }

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 55; j++)
        {
            if ((i == 1 || i == 2) && (j == theJpos || j == theJpos + 1))
            {
                
                if (matrix[i][j] == "S ")
                {
                    matrix[i][j] = "X ";
                    money+=10;
                   
                }
                if (matrix[i][j+1] == "S ")
                {
                    matrix[i][j+1] = "X ";
                }
                break;
            }
        }

    }
}

void Board::getBox(int posX, int posY, int& x, int& y)
{
    if (posY==9||posY==10)
    {
        y = 6;
    }
    else if(posY == 12 || posY == 13)
    {
        y = 9;
    }
    else if (posY == 15 || posY == 16)
    {
        y = 12;
    }
    else if (posY == 18 || posY == 19)
    {
        y = 15;
    }
    else if (posY == 21 || posY == 22)
    {
        y = 18;
    }
    else
    {

    }

    if (posX==20||posX==21||posX==22)
    {
        x = 10;
    }
    else if (posX == 26 || posX == 27 || posX == 28)
    {
        x = 13;
    }
    else if (posX == 32 || posX == 33 || posX == 34)
    {
        x = 16;
    }
    else if (posX == 38 || posX == 39 || posX == 40)
    {
        x = 19;
    }
    else if (posX == 44 || posX == 45 || posX == 46)
    {
        x = 22;
    }
    else if (posX == 50 || posX == 51 || posX == 52)
    {
        x = 25;
    }
    else if (posX == 56 || posX == 57 || posX == 58)
    {
        x = 28;
    }
    else if (posX == 62 || posX == 63|| posX == 64)
    {
        x = 31;
    }
    else if (posX == 68 || posX == 69 || posX == 70)
    {
        x = 34;
    }
    else
    {

    }


}

void Board::plantSunflower(int x, int y)
{
    if (money>=20)
    {
        if  ((matrix[x][y] == ". ") && (matrix[x + 1][y] == ". ") && (matrix[x][y + 1] == ". ") && (matrix[x + 1][y + 1] == ". "))
        {
            matrix[x][y] = "S ";
            matrix[x + 1][y] = "S ";
            matrix[x][y + 1] = "S ";
            matrix[x + 1][y + 1] = "S ";

            SunFlowers[sunFlowercount].setPos(x, x + 1, y, y + 1);
            sunFlowercount++;
            money -= 20;
        }
       
    }
    else
    {

    }
   
}

void Board::plantPea(int x, int y)
{
    if (money >= 50)
    {
        if ((matrix[x][y]==". " )&&( matrix[x + 1][y] == ". ")&&(matrix[x][y + 1] == ". ")&&(matrix[x + 1][y + 1] == ". "))
        {
            matrix[x][y] = "P ";
            matrix[x + 1][y] = "P ";
            matrix[x][y + 1] = "P ";
            matrix[x + 1][y + 1] = "P ";

            Peas[peaCount].setPos(x, x + 1, y, y + 1);
            peaCount++;
            money -= 50;
        }
       
    }
    else
    {

    }
}

void Board::PeaShoot(int z)
{
    int x2;
    int y2;

    
        x2 = Peas[z].getX2();
        y2 = Peas[z].getY2();

       
        matrix[x2][y2+1] = "> ";
                    

             
       

       
        if (Peas[z].getShot()==0)
        {
            Peas[z].setProjPos(y2);
        }

        Peas[z].setShot();
        
}

void Board::moveProjOnce(int i)
{
   
    matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "P ";
    matrix[Peas[i].getX2()][Peas[i].getProjPos()+1] = "  ";

    matrix[Peas[i].getX2()][Peas[i].getProjPos()+2] = "> ";

    int z = Peas[i].getProjPos();

    Peas[i].setProjPos(z+2);

}

void Board::moveProjOnePosition(int i)
{
    

    if (Peas[i].getProjPos() <=38)
    {
        if (Peas[i].getProjPos() % 3 == 0)
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "  ";
        }
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos()] == "P ")
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "P ";

        }
        else if ((Peas[i].getProjPos() == 37) && (matrix[Peas[i].getX2()][Peas[i].getProjPos() + 1] !="Z"))
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "/ ";

        }
        else if (matrix[Peas[i].getX2()-1][Peas[i].getProjPos()+1] == "P ")
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "P ";
            matrix[Peas[i].getX2()][Peas[i].getProjPos() +1] = "P ";

        }
        else if (matrix[Peas[i].getX2() - 1][Peas[i].getProjPos()] == "P ")
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "P ";
            matrix[Peas[i].getX2()][Peas[i].getProjPos() + 1] = "P ";

        }
        else if (matrix[Peas[i].getX2()-1][Peas[i].getProjPos() + 1] == "S ")
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "S ";
            matrix[Peas[i].getX2()][Peas[i].getProjPos() + 1] = "S ";

        }
        else if (matrix[Peas[i].getX2()-1][Peas[i].getProjPos()] == "S ")
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = "S ";
            matrix[Peas[i].getX2()][Peas[i].getProjPos() + 1] = "S ";

        }

        // VERIFICA!
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() +1] == "Z ")
        {
            
            
            for (int g = 0; g < zombieCount; g++)
            {
                if (Zombies[g].getX1() == Peas[i].getX2())
                {
                    Zombies[g].lowerHP();
                    
                }
            }

        }
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos()] == "Z ")
        {

            for (int g = 0; g < zombieCount; g++)
            {
                if (Zombies[g].getX1() == Peas[i].getX2())
                {
                    Zombies[g].lowerHP();

                }
            }

        }
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() +2] == "Z ")
        {
           

            for (int g = 0; g < zombieCount; g++)
            {
                if (Zombies[g].getX1() == Peas[i].getX2())
                {
                    Zombies[g].lowerHP();

                }
            }

        }
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() + 3] == "Z ")
        {


            for (int g = 0; g < zombieCount; g++)
            {
                if (Zombies[g].getX1() == Peas[i].getX2())
                {
                    Zombies[g].lowerHP();

                }
            }

        }
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() -1] == "Z ")
        {


            for (int g = 0; g < zombieCount; g++)
            {
                if (Zombies[g].getX1() == Peas[i].getX2())
                {
                    Zombies[g].lowerHP();

                }
            }

        }
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() + 1] == "G ")
        {


        for (int g = 0; g < bucketCount; g++)
        {
            if (BZombies[g].getX1() == Peas[i].getX2())
            {
                BZombies[g].lowerHP();

            }
        }

        }
        else if (matrix[Peas[i].getX2()][Peas[i].getProjPos()] == "G ")
        {

        for (int g = 0; g < bucketCount; g++)
        {
            if (BZombies[g].getX1() == Peas[i].getX2())
            {
                BZombies[g].lowerHP();

            }
        }

        }
       /* else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() + 2] == "G ")
        {


        for (int g = 0; g < bucketCount; g++)
        {
            if (BZombies[g].getX1() == Peas[i].getX2())
            {
                BZombies[g].lowerHP();

            }
        }

        }*/
        /*else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() + 3] == "G ")
        {


        for (int g = 0; g < bucketCount; g++)
        {
            if (BZombies[g].getX1() == Peas[i].getX2())
            {
                BZombies[g].lowerHP();

            }
        }

        }*/
        /*else if (matrix[Peas[i].getX2()][Peas[i].getProjPos() - 1] == "G ")
        {


        for (int g = 0; g < bucketCount; g++)
        {
            if (BZombies[g].getX1() == Peas[i].getX2())
            {
                BZombies[g].lowerHP();

            }
        }

        }*/

        else
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos()] = ". ";
        }

        if (Peas[i].getProjPos() != 37)
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos() + 1] = "> ";
        }
        else
        {
            matrix[Peas[i].getX2()][Peas[i].getProjPos() + 1] = "/ ";
            Peas[i].resetShot();
        }

       

        
        
        if (Peas[i].getShot()==1)
        {
            Peas[i].setProjPos(Peas[i].getProjPos() + 1);
        }
        else
        {
            Peas[i].setProjPos(Peas[i].getY2());
        }
       
    }
    
   
}

bool Board::CheckZombieSpawn()
{
    srand(time(NULL));

    int randomNumber;

    randomNumber = rand() % 100 + 1;

    if (randomNumber % 4 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Board::setPositionForZombie()
{
    srand(time(NULL));

    int randomNumber;
    
    randomNumber = rand() % 5 + 1;

    return randomNumber;
}

void Board::printZombie(int x)
{
    Zombies[zombieCount].setAlive();
    Zombies[zombieCount].setFresh();

    if (x==1)
    {
        if (matrix[7][38] != "X" &&zFull1<1)
        {
            matrix[7][38] = "X";
            Zombies[zombieCount].setCor(7, 38);
            zombieCount++;
            zFull1++;
        }
        
    }
    else if (x == 2)
    {
        if (matrix[10][38] != "X" && zFull2<1)
        {
            matrix[10][38] = "X";
            Zombies[zombieCount].setCor(10, 38);
            zombieCount++;
            zFull2++;
        }
    }
    else if (x == 3)
    {
        if (matrix[13][38] != "X" && zFull3 <1)
        {
            matrix[13][38] = "X";
            Zombies[zombieCount].setCor(13, 38);
            zombieCount++;
            zFull3++;
        }
    }
    else if (x == 4)
    {
        if (matrix[16][38] != "X" &&zFull4<1)
        {
            matrix[16][38] = "X";
            Zombies[zombieCount].setCor(16, 38);
            zombieCount++;
            zFull4++;
        }
    }
    else
    {
        if (matrix[19][38] != "X" &&zFull5<1)
        {
            matrix[19][38] = "X";
            Zombies[zombieCount].setCor(19, 38);
            zombieCount++;
            zFull5++;
        }
    }

    

   
    
}

void Board::moveZombie(int i)
{
    int X1 = Zombies[i].getX1();
    int Y1 = Zombies[i].getY1();

    
    
    string aux;

    if (matrix[X1][Y1 - 1]=="S ")
    {
        for (int i = 0; i < sunFlowercount; i++)
        {
            if (X1==SunFlowers[i].getX1() || X1==SunFlowers[i].getX2())
            {
                SunFlowers[i].lowerHP();
            }
            if (SunFlowers[i].getHP()<=0)
            {
                matrix[X1][Y1 - 1] = ". ";
                matrix[X1-1][Y1 - 1] = ". ";
                matrix[X1][Y1 - 2] = ". ";
                matrix[X1 - 1][Y1 - 2] = ". ";
            }
        }
    }
    else if (matrix[X1][Y1 - 1] == "P ")
    {
        for (int i = 0; i < peaCount; i++)
        {
            if (X1 == Peas[i].getX1() || X1 == Peas[i].getX2())
            {
                Peas[i].lowerHP();
            }
            if (Peas[i].getHP() <= 0)
            {
                matrix[X1][Y1 - 1] = ". ";
                matrix[X1 - 1][Y1 - 1] = ". ";
                matrix[X1][Y1 - 2] = ". ";
                matrix[X1 - 1][Y1 - 2] = ". ";
                Peas[i].dead = 1;
            }
        }
    }
    else
    {
        if (Y1 > 9)
        {
            aux = matrix[X1][Y1 - 1];
            matrix[X1][Y1 - 1] = "Z ";
            matrix[X1][Y1] = Zombies[i].lastPos;
            Zombies[i].lastPos = aux;
            Zombies[i].lowerY1();
        }

        if (Y1 == 9 && matrix[X1][Y1] == "Z ")
        {
            matrix[X1][Y1] = "  ";
            gameOver = 1;

        }

        if (Zombies[i].getHP() <= 0)
        {

            score += 25;
            Zombies[i].getKilled();
            matrix[X1][Y1] = Zombies[i].lastPos;

        }
    }
    

    

    
    

}



bool Board::checkZombieSpawnFull(int x)
{
    if (x == 1)
    {
        if (matrix[7][38] != "Z" && zFull1 < 3)
        {
            return 1;
        }

    }
    else if (x == 2)
    {
        if (matrix[10][38] != "Z" && zFull2 < 3)
        {
            return 1;
        }
    }
    else if (x == 3)
    {
        if (matrix[13][38] != "Z" && zFull3 < 3)
        {
            return 1;
        }
    }
    else if (x == 4)
    {
        if (matrix[16][38] != "Z" && zFull4 < 3)
        {
            return 1;
        }
    }
    else
    {
        if (matrix[19][38] != "Z" && zFull5 < 3)
        {
            return 1;
            
        }
    }
    return 0;
}

void Board::printZombie2(int x)
{
    ZombiesWave2[zombieCount].setAlive();
    ZombiesWave2[zombieCount].setFresh();

    if (x == 1)
    {
        if (matrix[7][38] != "X" && zFull1 < 1)
        {
            matrix[7][38] = "X";
            ZombiesWave2[zombieCount].setCor(7, 38);
            zombieCount++;
            zFull1++;
        }

    }
    else if (x == 2)
    {
        if (matrix[10][38] != "X" && zFull2 < 1)
        {
            matrix[10][38] = "X";
            ZombiesWave2[zombieCount].setCor(10, 38);
            zombieCount++;
            zFull2++;
        }
    }
    else if (x == 3)
    {
        if (matrix[13][38] != "X" && zFull3 < 1)
        {
            matrix[13][38] = "X";
            ZombiesWave2[zombieCount].setCor(13, 38);
            zombieCount++;
            zFull3++;
        }
    }
    else if (x == 4)
    {
        if (matrix[16][38] != "X" && zFull4 < 1)
        {
            matrix[16][38] = "X";
            ZombiesWave2[zombieCount].setCor(16, 38);
            zombieCount++;
            zFull4++;
        }
    }
    else
    {
        if (matrix[19][38] != "X" && zFull5 < 1)
        {
            matrix[19][38] = "X";
            ZombiesWave2[zombieCount].setCor(19, 38);
            zombieCount++;
            zFull5++;
        }
    }
}

void Board::printZombieG(int x)
{
    BZombies[bucketCount].setAlive();
    BZombies[bucketCount].setFresh();

    if (x == 1)
    {
        if (matrix[7][38] != "X" && BzFull1 < 1)
        {
            matrix[7][38] = "X";
            BZombies[bucketCount].setCor(7, 38);
            bucketCount++;
            BzFull1++;
        }

    }
    else if (x == 2)
    {
        if (matrix[10][38] != "X" && BzFull2 < 1)
        {
            matrix[10][38] = "X";
            BZombies[bucketCount].setCor(10, 38);
            bucketCount++;
            BzFull2++;
        }
    }
    else if (x == 3)
    {
        if (matrix[13][38] != "X" && BzFull3 < 1)
        {
            matrix[13][38] = "X";
            BZombies[bucketCount].setCor(13, 38);
            bucketCount++;
            BzFull3++;
        }
    }
    else if (x == 4)
    {
        if (matrix[16][38] != "X" && BzFull4 < 1)
        {
            matrix[16][38] = "X";
            BZombies[bucketCount].setCor(16, 38);
            bucketCount++;
            BzFull4++;
        }
    }
    else
    {
        if (matrix[19][38] != "X" && BzFull5 < 1)
        {
            matrix[19][38] = "X";
            BZombies[bucketCount].setCor(19, 38);
            bucketCount++;
            BzFull5++;
        }
    }
}

void Board::moveZombieG(int i)
{
    int X1 = BZombies[i].getX1();
    int Y1 = BZombies[i].getY1();



    string aux;

    if (matrix[X1][Y1 - 1] == "S ")
    {
        for (int i = 0; i < sunFlowercount; i++)
        {
            if (X1 == SunFlowers[i].getX1() || X1 == SunFlowers[i].getX2())
            {
                SunFlowers[i].lowerHP();
            }
            if (SunFlowers[i].getHP() <= 0)
            {
                matrix[X1][Y1 - 1] = ". ";
                matrix[X1 - 1][Y1 - 1] = ". ";
                matrix[X1][Y1 - 2] = ". ";
                matrix[X1 - 1][Y1 - 2] = ". ";
            }
        }
    }
    else if (matrix[X1][Y1 - 1] == "P ")
    {
        for (int i = 0; i < peaCount; i++)
        {
            if (X1 == Peas[i].getX1() || X1 == Peas[i].getX2())
            {
                Peas[i].lowerHP();
            }
            if (Peas[i].getHP() <= 0)
            {
                matrix[X1][Y1 - 1] = ". ";
                matrix[X1 - 1][Y1 - 1] = ". ";
                matrix[X1][Y1 - 2] = ". ";
                matrix[X1 - 1][Y1 - 2] = ". ";
                Peas[i].dead = 1;
            }
        }
    }
    else
    {
        if (Y1 > 9)
        {
            aux = matrix[X1][Y1 - 1];
            matrix[X1][Y1 - 1] = "G ";
            matrix[X1][Y1] = BZombies[i].lastPos;
            BZombies[i].lastPos = aux;
            BZombies[i].lowerY1();
        }

        if (Y1 == 9 && matrix[X1][Y1] == "G ")
        {
            matrix[X1][Y1] = "  ";
            gameOver = 1;
            victory = 1;

        }

        if (BZombies[i].getHP() <= 0)
        {

            score += 50;
            BZombies[i].getKilled();
            matrix[X1][Y1] = BZombies[i].lastPos;

        }
    }

    
}

void Board::moveZombie2(int i)
{
    int X1 = ZombiesWave2[i].getX1();
    int Y1 = ZombiesWave2[i].getY1();



    string aux;


    if (Y1 > 9)
    {
        aux = matrix[X1][Y1 - 1];
        matrix[X1][Y1 - 1] = "Z ";
        matrix[X1][Y1] = ZombiesWave2[i].lastPos;
        ZombiesWave2[i].lastPos = aux;
        ZombiesWave2[i].lowerY1();
    }

    if (Y1 == 9 && matrix[X1][Y1] == "Z ")
    {
        matrix[X1][Y1] = "  ";
        gameOver = 1;

    }

    if (ZombiesWave2[i].getHP() <= 0)
    {

        score += 25;
        ZombiesWave2[i].getKilled();
        matrix[X1][Y1] = Zombies[i].lastPos;

    }

}
