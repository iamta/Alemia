#include<iostream>
#include<windows.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include<fstream>

#include"LoadingScreen.h"
#include"TitleScreen.h"
#include"Board.h"
#include"ConsoleInput.h"
#include"ConsoleOutput.h"
#include"Sun.h"
#include"ZombieFather.h"
#include"Zombie.h"



#pragma comment(lib, "winmm.lib")
bool closeGame = 0;

using namespace std;

void wait(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait) {}
}




int main()
{
    /*ofstream EventLogFile;
    EventLogFile.open("eventLogs.txt");
    EventLogFile << "  a\n";*/
    string logEv = " ";
    
    

    PlaySound("music.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    LoadingScreen::getInstance()->DisplayLoadingScreen();
    LoadingScreen::getInstance()->DestroyInstance();

    TitleScreen::getInstance()->DisplayTitleScreen();
    TitleScreen::getInstance()->getLogs();
    TitleScreen::getInstance()->DestroyInstance();

    

    
    UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
    UserInterface::ConsoleInput conIn = UserInterface::ConsoleInput::getInstance();

    Sun SunController;

    bool clickSunflower = 0;
    bool clickPea = 0;
    int k = 0;
    int SunPos;
    int Xpos;
    int Ypos;
    int collectSunPos;
    int xBox = 0;
    int yBox = 0;
    int zombiePosition;

    int spawnZombieCounter = 0;
    bool secondWaveRewind = 0;
    int gameClock = 0;
    int timer = 200;

    int peaNumber;

    int zombieCounter1 = 0;
    int zombieCounter = 0;
    int shootPeaCounter = 0;

    while (Board::getInstance()->getGameOver()!=1)
    {
       /* Board::getInstance()->PrintBoard();
        Sleep(1000);*/

        Ypos = -99;
        Xpos = -99;
        peaNumber = Board::getInstance()->getPeanumber();

        SunController.CheckSun(Board::getInstance()->getSunFlowerCount());
        if (SunController.getBool() == 1)
        {
            SunPos = SunController.getSunPosition();
            Board::getInstance()->renewSun(SunPos);



           
            SunController.resetSun();

        }

        


        conOut(1, 0) << "  SCORE: " << Board::getInstance()->getScore() << "      \n";
        conOut(2, 0) << "  RESOURCES: " << Board::getInstance()->getRes() << "      "<<"\n";

        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 55; j++)
            {
                cout << Board::getInstance()->getMat(i,j);
            }
            cout << endl;
        }
        
        std::string action = conIn.getUserActions();
		if (action != "")
		{

			conOut(41, 2) << action;
            Xpos = conIn.lastX;
            Ypos = conIn.lastY;
           
            if ((Ypos==4||Ypos==5))
            {
                clickSunflower = 0;
              collectSunPos =  Board::getInstance()->clickSun(Xpos);
              if (collectSunPos != - 999)
              {
                  Board::getInstance()->collectSun(collectSunPos);
                  logEv = logEv + "Clicked Sun\n";
                  
              }
            }
            
            else if ((Ypos==9||Ypos==10 )&&(Xpos == 2 || Xpos == 3 || Xpos == 4))
            {
               
                    clickSunflower = 1;
                    clickPea = 0;
                    conOut(40, 2) << "ClickSunFlower " << "     ";
                    logEv = logEv + "Clicked SunFlower\n";
                
            }
            else if((Ypos == 12 || Ypos == 13) && (Xpos == 2 || Xpos == 3 || Xpos == 4))
            {
                clickSunflower = 0;
                clickPea = 1;
                conOut(40, 2) << "ClickPea " << "     ";
                logEv = logEv + "Clicked Pea\n";
            }
            else if (Ypos == 9 || Ypos == 10 || Ypos == 12 || Ypos == 13 || Ypos == 15 || Ypos == 16||Ypos==18||Ypos==19||Ypos==21||Ypos==22)
            {
                if (Xpos==20||Xpos==21||Xpos==22||Xpos==26||Xpos==27||Xpos==28||Xpos==32||Xpos==33||Xpos==34||Xpos==38||Xpos==39||Xpos==40||Xpos==44||Xpos==45||Xpos==46||Xpos==50||Xpos==51||Xpos==52||Xpos==56||Xpos==57||Xpos==58||Xpos==62||Xpos==63||Xpos==64||Xpos==68||Xpos==69||Xpos==70)
                {
                    if (clickSunflower == 1)
                    {
                        conOut(40, 2) << "Getting Box SF" << "     ";
                        Board::getInstance()->getBox(Xpos, Ypos, yBox, xBox); // yBox apoi xBox
                        Board::getInstance()->plantSunflower(xBox, yBox);  // invers!!!
                        clickSunflower = 0;
                        logEv = logEv + "SunFlower Planted\n";
                    }
                    if (clickPea == 1)
                    {
                        conOut(40, 2) << "Getting Box P" << "     ";
                        Board::getInstance()->getBox(Xpos, Ypos, yBox, xBox);
                        Board::getInstance()->plantPea(xBox, yBox);
                        clickPea = 0;
                        logEv = logEv + "Pea Planted\n";
                    }
                    
                }
            }
            else
            {
                conOut(40, 2) << "EMPTY" << "     ";
                clickSunflower = 0;
                clickPea = 0;
                
               
            }
           
            
		}

        
            for (int i = 0; i < peaNumber; i++)
            {
                if (Board::getInstance()->getPea(i).getShot() == 0)
                {
                    Board::getInstance()->PeaShoot(i);


                }
                else
                {
                    if (shootPeaCounter % 3 == 0 && Board::getInstance()->getPea(i).dead==0)
                    {
                        Board::getInstance()->moveProjOnePosition(i);
                        /* if (Board::getInstance()->getPea(i).getProjPos() == Board::getInstance()->getPea(i).getY2())
                         {
                             Board::getInstance()->moveProjOnce(i);
                             cout << Board::getInstance()->getPea(i).getProjPos();
                         }*/

                         /* else if (Board::getInstance()->getPea(i).getProjPos()>50)
                          {
                              Board::getInstance()->moveProjOnePosition(i);
                          }*/
                    }
                }

            }
           shootPeaCounter++;
        
           /*if (Board::getInstance()->CheckZombieSpawn() == 1)
           {
               zombiePosition = Board::getInstance()->setPositionForZombie();
               Board::getInstance()->getZombie(zombieCounter).setAlive();
               if (zombieCounter<=10)
               {
                   if (Board::getInstance()->checkZombieSpawnFull(zombiePosition) == 1)
                   {
                       zombieCounter++;
                      
                   }
               }
               
               

           }

           for (int i = 0; i < zombieCounter; i++)
           {
               if (Board::getInstance()->getZombie(i).getFresh()==0)
               {
                   Board::getInstance()->printZombie(zombiePosition);
               }
              
               else
               {
                   Board::getInstance()->moveZombie(i);
               }
                   
               
           }*/

           if (gameClock<=timer +1000)
           {
               if (zombieCounter1 <= 3)
               {
                   if (spawnZombieCounter % 10 == 0)
                   {
                       if (Board::getInstance()->CheckZombieSpawn() == 1)
                       {
                           zombiePosition = Board::getInstance()->setPositionForZombie();
                           Board::getInstance()->printZombie(zombiePosition);
                           logEv = logEv + "Zombie Spawned\n";
                          
                       }

                       for (int i = 0; i < Board::getInstance()->getZombieNumber(); i++)
                       {
                           if (Board::getInstance()->getZombie(i).getAlive() == 1)
                           {
                               Board::getInstance()->moveZombie(i);

                               
                           }
                       }
                   }
               }

               if (zombieCounter1 > 3 && gameClock >= timer)
               {
                   if (spawnZombieCounter % 15 == 0)
                   {
                       if (secondWaveRewind == 0)
                       {
                           Board::getInstance()->rewindZombieCounter();
                           Board::getInstance()->rewindZFull();
                           secondWaveRewind = 1;
                       }


                       if (Board::getInstance()->CheckZombieSpawn() == 1)
                       {
                           zombiePosition = Board::getInstance()->setPositionForZombie();
                           Board::getInstance()->printZombie(zombiePosition);

                       }

                       for (int i = 0; i < Board::getInstance()->getZombieNumber(); i++)
                       {
                           if (Board::getInstance()->getZombie2(i).getAlive() == 1)
                           {
                               Board::getInstance()->moveZombie(i);
                               
                           }
                       }
                   }
               }






              
           }
          if(gameClock>timer + 500)
           {
               if ((spawnZombieCounter % 10) == 0)
               {
                   if (Board::getInstance()->CheckZombieSpawn() == 1)
                   {
                       zombiePosition = Board::getInstance()->setPositionForZombie();
                       Board::getInstance()->printZombieG(zombiePosition);
                       logEv = logEv + "Bucket Zombie Spawned\n";

                   }

                   for (int i = 0; i < Board::getInstance()->getZombieGNumber(); i++)
                   {
                       if (Board::getInstance()->getZombieG(i).getAlive() == 1)
                       {
                           Board::getInstance()->moveZombieG(i);

                       }
                   }
               }
           }

           spawnZombieCounter++;

           gameClock++;


           
          

         
       
           conOut(42, 2) <<gameClock<<"          ";
          

       
        
        

    }

    Board::getInstance()->DestroyInstance();

    if (gameClock >= 1000)
    {
        conOut(42, 2) << "Victory!";
        logEv = logEv + "Victory!\n";
    }
    else
    {
        conOut(42, 2) << "Game Over!";
        logEv = logEv + "Game Over!\n";
    }

    
    ofstream outFile;
    outFile.open("EvenimenteLogs.txt");

    outFile << logEv;

    
   
    
}