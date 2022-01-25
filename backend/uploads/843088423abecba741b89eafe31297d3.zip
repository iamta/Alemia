#include "CGame.h"

#define linedistance 15


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawpixel2(unsigned char x, unsigned char y, unsigned char Color, char character) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

	gotoxy(x, y); printf("%c", character);
}
void setcolor(WORD color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}
void drawpixel(unsigned char x, unsigned char y, unsigned char Color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);

	gotoxy(x, y); printf("Û");
}
void drawline(int x0, int y0, int x1, int y1, int color) {
	int pix = color;
	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; }
	else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; }
	else { stepx = 1; }
	dy <<= 1;                                                  // dy is now 2*dy
	dx <<= 1;                                                  // dx is now 2*dx

	drawpixel(x0, y0, pix);
	if (dx > dy) {
		int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;                                // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy;                                    // same as fraction -= 2*dy
			drawpixel(x0, y0, pix);
		}
	}
	else {
		int fraction = dx - (dy >> 1);
		while (y0 != y1) {
			if (fraction >= 0) {
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			drawpixel(x0, y0, pix);
		}
	}
}
void drawfilledrectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char bkcol) {
	int x, y;
	setcolor(bkcol);                       //Set to color bkcol

	for (y = y1; y < y2; y++) {                    //Fill Y Region Loop
		for (x = x1; x < x2; x++) {              //Fill X region Loop
			gotoxy(x, y); drawpixel(x, y, bkcol);      //Draw Solid space
		}
	}
}
void drawframe(unsigned x, unsigned y, unsigned sx, unsigned sy, const char text_[]) {
	unsigned i, j, m; {

		m = (sy - y);                       //differential
		j = m / 2;                          //adjust
		j = j + 1;                          //more adjustment
		gotoxy(x, y); printf("É");       //Top left corner of drawframe
		gotoxy(sx, y); printf("»");      //Top right corner of drawframe
		gotoxy(x, sy); printf("È");      //Bottom left corner of drawframe
		gotoxy(sx, sy); printf("¼");     //Bottom right corner of drawframe

		for (i = x + 1; i < sx; i++) {
			gotoxy(i, y); printf("Í");     // Top horizontol line
			gotoxy(i, sy); printf("Í");    // Bottom Horizontal line
		}

		for (i = y + 1; i < sy; i++) {
			gotoxy(x, i); printf("º");     //Left Vertical line
			gotoxy(sx, i); printf("º");    //Right Vertical Line
		}

		gotoxy(x + j, y + j - 1); printf(text_); //put Title
		gotoxy(1, 24);
	}
}
void drawwindow(unsigned x, unsigned y, unsigned sx, unsigned sy, unsigned char bkcol, const char text_[]) {
	drawfilledrectangle(x, y, sx, sy, bkcol);
	drawframe(x, y, sx, sy, text_);
}

void CGame::Afisare_Meniu()
{
	drawwindow(72, 12, 80, 14, 2, men.GetStart().c_str());
	drawwindow(72, 16, 82, 18, 2, men.GetOption().c_str());
	drawwindow(72, 20, 84, 22, 2, men.GetClasament().c_str());
	drawwindow(72, 24, 79, 26, 2, men.GetExit().c_str());
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
}

void CGame::doLoadingBar()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);

	static UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	static auto begin = steady_clock::now();
	int col = COL_FIRST_STAR_POSITION;
	auto end = steady_clock::now();
	static std::string s = "*****";
	conOut(ROW_TITLE, COL_FIRST_STAR_POSITION + 5) << "LOADING";
	for (char c : s)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		conOut(ROW_TITLE + 1, col) << c;
		for (int i = 0; i < 5; i++)
			cout << " ";
		std::cout << std::flush;
		col += COL_DISTANCE_BETWEEN_STARS;
	}
	system("cls");
	//SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void CGame::Afisare_coord()
{

	std::string action; 
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

		for(int i=0;i<10;i++)
		{
			//conOut(41, 2) << action;
			action = conIn.getUserActions();
		} /*while (!strstr(action.c_str(),"simple"));*/
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);


}

void CGame::afisare_optiuni()
{

		drawwindow(51, 13, 61, 15, 2, "level 1");
		drawwindow(71, 13, 81, 15, 2, "level 2");
		drawwindow(91, 13, 101, 15, 2, "level 3");
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

		while (true)
		{
			conIn.getUserActions();
			if (conIn.coord.y > 12 && conIn.coord.y < 16)
			{
				if (conIn.coord.x > 50 && conIn.coord.x < 62)
				{
					op.SetLevel(0);
					break;
				}
				else if (conIn.coord.x > 70 && conIn.coord.x < 82)
				{
					op.SetLevel(1);
					break;
				}
				else if (conIn.coord.x > 90 && conIn.coord.x < 102)
				{
					op.SetLevel(2);
					break;
				}


			}
		}
		system("cls");
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
		Sleep(300);
}

void CGame::afisare_teren()
{

	
		for (int i = 0; i <= 25; i += 5)
			drawline(ter.Get_xlu(), ter.Get_ylu() + i, ter.Get_xrd(), ter.Get_ylu() + i, ter.GetColor());
		//rows
		for (int i = 0; i <= ter.Get_xrd(); i += 15)
			drawline(ter.Get_xlu() + i, ter.Get_ylu()+(5*op.GetLevel()), ter.Get_xlu() + i, ter.Get_yrd() - (5 * op.GetLevel()), ter.GetColor());
	

	//board
	//lines 
	for (int i = 0; i <= 5; i += 5)
		drawline(ter.Get_Txlu(), ter.Get_Tylu() + i, ter.Get_Txrd(), ter.Get_Tylu() + i, ter.GetTColor());
	//rows
	for (int i = 0; i <= ter.Get_Txrd(); i += 15)
		drawline(ter.Get_Txlu() + i, ter.Get_Tylu(), ter.Get_Txlu() + i, ter.Get_Tyrd(), ter.GetTColor());
}

void CGame::afisare_plante()
{
	ShotPlants p1;
	SunFlower p2;
	PotatoPlants p3;
	DoubleShootPlants p4;
	BombPlants p5;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	int k = 0;
	//afisam prima planta din tabela
	conOut(2, 15) << p1.GetName() + " " + std::to_string(p1.GetCost()) + "$";
	for (int i = 5; i < 8; i++)
		for (int j = 15; j < 18; j++, k++)
			conOut(i, j) << p1.GetForma()[k];
	//afisam a doua planta din tabela
	k = 0;
	conOut(2, 30) << p2.GetName() + " " + std::to_string(p2.GetCost()) + "$";
	for (int i = 5; i < 8; i++)
		for (int j = 30; j < 33; j++, k++)
			conOut(i, j) << p2.GetForma()[k];
	//afisam a tria planta din tabela
	k = 0;
	conOut(2, 45) << p3.GetName() + " " + std::to_string(p3.GetCost()) + "$";
	for (int i = 5; i < 8; i++)
		for (int j = 45; j < 48; j++, k++)
			conOut(i, j) << p3.GetForma()[k];
	//afisam a patra planta din tabela
	k = 0;
	conOut(2, 60) << p4.GetName() + " " + std::to_string(p4.GetCost()) + "$";
	for (int i = 5; i < 8; i++)
		for (int j = 60; j < 66; j++, k++)
			conOut(i, j) << p4.GetForma()[k];
	//afisam a cincea planta din tabela
	k = 0;
	conOut(2, 75) << p5.GetName() + " " + std::to_string(p5.GetCost()) + "$";
	for (int i = 5; i < 8; i++)
		for (int j = 75; j < 78; j++, k++)
			conOut(i, j) << p5.GetForma()[k];
}

bool Verify_Plants_Puts(int x,int y,int x_t1,int x_t2,int y_t1,int y_t2,int level)
{
	if (x > x_t1&&x < x_t2)
	{
		if (y > y_t1 + (5 * level) && y < y_t2 - (5 * level))
		{
			return true;
		}
	}
	return false;
}

bool Approximate_Coord(int *x, int *y, int x_t1, int x_t2, int y_t1, int y_t2, int level)
{
	int a = 0;
	for (int i = 0; i < ((x_t2-x_t1) / 9); i++)
	{
		if ((*x) > x_t1 + i * ((x_t2-x_t1) / 9) && (*x) < (i + 1)*((x_t2 - x_t1) / 9) + x_t1)
		{
			(*x) = x_t1 + i * ((x_t2 - x_t1) / 9) + 5;
			a++;
			break;
		}
	}
	for (int i = 0; i < (5-2*level); i++)
	{
		if ((*y) > (y_t1+(5*level) + i * (((y_t2 - y_t1) -(5*level)) / 5) )&& (*y) < (y_t1+ (5*level))+ (i + 1)*(((y_t2 - y_t1) -(5*level)) / 5))
		{
			(*y) = (y_t1 + (5 * level)) + i * (((y_t2 - y_t1) - (5 * level)) / 5) + 2+i*level;
			a++;
			break;
		}
	}
	if (a == 2)
		return true;
	else
		return false;
}

template <typename T>
bool VP(vector <T> plant, int x, int y)
{
	for (auto &c : plant)
	{
		if (c.GetX() == x && c.GetY() == y)
		{
			return false;
		}
	}
	return true;
}
	
bool CGame::TakeMoney(int x)
{
	if (money.GetMoney() >= x)
	{
		money.SetMoney(-x);
		return true;
	}
	return false;
}

void CGame::Log()
{
	drawframe(71, 15, 101, 17, "Names: ");
	char c = ' ';
	string name;
	int x = 83;
	do
	{
		if (c != ' ')
			name += c;
		scanf_s("%c", &c);
		conOut(16, x) << c;
		x++;
	} while (c != '\r');
	PN.SetName(name);
	PN.compare();
	//
	for (int j = 15; j < 19; j++)
		for (int i = 68; i < 112; i++)
			conOut(j, i) << "   ";

}

void CGame::put_plants()
{
	int k = 0;
	Afisare_coord();
	if (conIn.coord.y > 2 && conIn.coord.y < 9 && (conIn.coord.x > 9 && conIn.coord.x < 86))
	{
		x = 0;
		for (int i = 10; i < 86; i += 15)
		{
			if (conIn.coord.x > i&&conIn.coord.x < (i + 15))
				x = (i - 10) / 15 + 1;
		}
	}

	for (int i = 0; i < 4; i++)
		Afisare_coord();


	if (x == 1)
	{

		if (Verify_Plants_Puts(conIn.coord.x, conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&(conIn.coord.x), &conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			VP(SP, (conIn.coord.x), conIn.coord.y) && VP(SF, (conIn.coord.x), conIn.coord.y) && VP(BP, (conIn.coord.x), conIn.coord.y) && VP(DSP, (conIn.coord.x), conIn.coord.y) && VP(PP, (conIn.coord.x), conIn.coord.y)&& TakeMoney(100))
		{
			ShotPlants p1;
			for (int i = conIn.coord.y; i < conIn.coord.y + 3; i++)
				for (int j = conIn.coord.x; j < conIn.coord.x + 3; j++, k++)
					conOut(i, j) << p1.GetForma()[k];

			p1.SetX(conIn.coord.x);
			p1.SetY(conIn.coord.y);
			SP.push_back(p1);
			x = 0;

		}
	}
	else if (x == 2)
	{

		if (Verify_Plants_Puts(conIn.coord.x, conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&(conIn.coord.x), &conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			VP(SP, (conIn.coord.x), conIn.coord.y) && VP(SF, (conIn.coord.x), conIn.coord.y) && VP(BP, (conIn.coord.x), conIn.coord.y) && VP(DSP, (conIn.coord.x), conIn.coord.y) && VP(PP, (conIn.coord.x), conIn.coord.y) && TakeMoney(50))
		{
			SunFlower p2;
			p2.SetX(conIn.coord.x);
			p2.SetY(conIn.coord.y);

			SF.push_back(p2);

			for (int i = conIn.coord.y; i < conIn.coord.y + 3; i++)
				for (int j = conIn.coord.x; j < conIn.coord.x + 3; j++, k++)
					conOut(i, j) << p2.GetForma()[k];
			x = 0;

		}

	}
	else if (x == 3)
	{

		if (Verify_Plants_Puts(conIn.coord.x, conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&(conIn.coord.x), &conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			VP(SP, (conIn.coord.x), conIn.coord.y) && VP(SF, (conIn.coord.x), conIn.coord.y) && VP(BP, (conIn.coord.x), conIn.coord.y) && VP(DSP, (conIn.coord.x), conIn.coord.y) && VP(PP, (conIn.coord.x), conIn.coord.y)&& TakeMoney(50))
		{
			PotatoPlants p3;
			p3.SetX(conIn.coord.x);
			p3.SetY(conIn.coord.y);

			PP.push_back(p3);
			for (int i = conIn.coord.y; i < conIn.coord.y + 3; i++)
				for (int j = conIn.coord.x; j < conIn.coord.x + 3; j++, k++)
					conOut(i, j) << p3.GetForma()[k];
			x = 0;

		}

	}
	else if (x == 4)
	{

		if (Verify_Plants_Puts(conIn.coord.x, conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&(conIn.coord.x), &conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			VP(SP, (conIn.coord.x), conIn.coord.y) && VP(SF, (conIn.coord.x), conIn.coord.y) && VP(BP, (conIn.coord.x), conIn.coord.y) && VP(DSP, (conIn.coord.x), conIn.coord.y) && VP(PP, (conIn.coord.x), conIn.coord.y) && TakeMoney(150))
		{
			DoubleShootPlants p4;
			p4.SetX(conIn.coord.x);
			p4.SetY(conIn.coord.y);

			DSP.push_back(p4);
			for (int i = conIn.coord.y; i < conIn.coord.y + 3; i++)
				for (int j = conIn.coord.x; j < conIn.coord.x + 6; j++, k++)
					conOut(i, j) << p4.GetForma()[k];
			x = 0;

		}
	}
	else if (x == 5)
	{

		if (Verify_Plants_Puts(conIn.coord.x, conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&(conIn.coord.x), &conIn.coord.y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			VP(SP, (conIn.coord.x), conIn.coord.y) && VP(SF, (conIn.coord.x), conIn.coord.y) && VP(BP, (conIn.coord.x), conIn.coord.y) && VP(DSP, (conIn.coord.x), conIn.coord.y) && VP(PP, (conIn.coord.x), conIn.coord.y) && TakeMoney(25))
		{
			BombPlants p5;
			p5.SetX(conIn.coord.x);
			p5.SetY(conIn.coord.y);
			BP.push_back(p5);
			for (int i = conIn.coord.y; i < conIn.coord.y + 3; i++)
				for (int j = conIn.coord.x; j < conIn.coord.x + 3; j++, k++)
					conOut(i, j) << p5.GetForma()[k];
			x = 0;
		}

	}


}

void CGame::SpawnSun()
{
	Sun sun1;
	int k = 0;
	srand(time(NULL));

	
	int x, y;
	static int ver = 0;
	bool ok = false;
	while (ok != true&&ver!= timp.elapsedTime())
	{
		
		x = rand() % ter.Get_xrd() - ter.Get_xlu();
		y = rand() % ter.Get_yrd() - ter.Get_ylu();
		if (Verify_Plants_Puts(x, y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&x, &y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel())&&
			VP(SP,x,y)&&VP(SF,x,y)&&VP(BP,x,y)&&VP(DSP,x,y)&&VP(PP,x,y))
		{
			sun1.SetX(x);
			sun1.SetY(y);
			for (int i = y; i < y + 3; i++)
				for (int j = x; j < x + 3; j++, k++)
					conOut(i, j) << sun1.GetForma()[k];
			sun.push_back(sun1);
			ok = true;
			ver = timp.elapsedTime();
			break;
		}
	}
}

void CGame::Clear(int x1, int y1, int x2, int y2)
{
	for (int i = x1; i < x2 ; i++)
		for (int j = y1; j < y2 ; j++)
			conOut(j, i) << " ";
}

void CGame::CatchSun()
{
	int k = 0;
	Afisare_coord();
	for(auto i=sun.begin();i!=sun.end();i++,k++)
		if (conIn.coord.x == (*i).GetX() && conIn.coord.y == (*i).GetY())
		{
			money.SetMoney(25);
			Clear((*i).GetX(), (*i).GetY(), (*i).GetX() + 3, (*i).GetY() + 3);
			sun.erase(i);
			conIn.coord.x = 0;
			conIn.coord.y = 0;
			break;
		}
	//Sleep(50);

}

void CGame::AfiseazaPuncte()
{
	Clear(120, 2, 126, 4);
	drawframe(120, 2, 126, 4, to_string(money.GetMoney()).c_str());
}

int VerifyRows(int x, int x_t, int space, int x_t1, int ax)
{
	for (int i = 0; i < (x_t1 - space) / 9; i++)
	{
		if (x == (i * ((x_t1 - space) / 9) + space)-ax)
			return 4;
	}
	return 1;
}

void CGame::SpawnZombie()
{
	srand(time(NULL));
	int x=ter.Get_xrd() -3, y;
	bool ok = false;
	static int ver = 0;
	while (ok != true&&ver!= timp.elapsedTime())
	{
		y = rand() % (ter.Get_yrd() +ter.Get_ylu()) - ter.Get_ylu();
		if (Verify_Plants_Puts(x, y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&x, &y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()))
		{
			Zombie bob(100, 25, " 9 -| / \\   ");
			bob.SetX(ter.Get_xrd() - 4);
			bob.SetY(y);
			zombie.push_back(bob);
			ok = true;
			ver = timp.elapsedTime();
		}
	}
}

void CGame::SpawnZombieBucket()
{
	srand(time(NULL));
	int x = ter.Get_xrd() - 3, y;
	bool ok = false;
	static int ver = 0;
	while (ok != true && ver != timp.elapsedTime())
	{
		y = rand() % (ter.Get_yrd() + ter.Get_ylu()) - ter.Get_ylu();
		if (Verify_Plants_Puts(x, y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()) &&
			Approximate_Coord(&x, &y, ter.Get_xlu(), ter.Get_xrd(), ter.Get_ylu(), ter.Get_yrd(), op.GetLevel()))
		{
			Zombie bob(150, 25, " O -| / \\   ");
			bob.SetX(ter.Get_xrd() - 4);
			bob.SetY(y);
			zombie.push_back(bob);
			ok = true;
			ver = timp.elapsedTime();
		}
	}
}


bool GetPP(vector<PotatoPlants> l, Zombie z)
{
	for (auto &p : l)
	if (p.GetX() + 4 == z.GetX())
		if (p.GetY() == z.GetY())
		{
			return false;
		}
	return true;
}


void Afisare_Sfarsit(UserInterface::ConsoleOutput conOut)
{
	conOut(36, 73) << "____      _______   _______   _________";
	conOut(37, 73) << "|   |     |  __  |  | ____|   |________|";
	conOut(38, 73) << "|   |     |  | | |  | |____      |  |   ";
	conOut(39, 73) << "|   |     |  | | |  |____  |     |  |   ";
	conOut(40, 73) << "|   |___  |  |_| |  ____|  |     |  |   ";
	conOut(41, 73) << "|_______| |______|  |______|     |__|   ";
	system("PAUSE");
	exit(0);
}

void CGame::Afiseaza_Zombie()
{
	int k = 0;
	int aux = 0;
	for (auto &c : zombie)
	{
		k = 0;
		if (c.GetTimp() % 2 == 0 && c.GetMove())
		{
			aux = VerifyRows(c.GetX(), 10, 10, ter.Get_xrd(), -1);
			if (aux == 4)
				aux++;

			for (int i = c.GetY(); i < c.GetY() + 3; i++)
				for (int j = c.GetX() + aux; j < c.GetX() + aux + 3; j++)
					conOut(i, j) << " ";

			for (int i = c.GetY(); i < c.GetY() + 3; i++)
				for (int j = c.GetX(); j < c.GetX() + 3; j++, k++)
					conOut(i, j) << c.GetForma()[k];

			c.SetX(c.GetX() - aux);
			if (VerifyRows(c.GetX(), 10, 10, ter.Get_xrd(), 4) == 4)
			{
				for (int i = c.GetY(); i < c.GetY() + 3; i++)
					for (int j = c.GetX() + 5; j < c.GetX() + 5 + 3; j++)
						conOut(i, j) << "  ";
			}
		}
	}
	//std::this_thread::sleep_for(0.5s);
}

template <typename T>
void Afiseaza_Proiectile(vector <T> &p,UserInterface::ConsoleOutput conOut, int nr)
{
	for (int i = 0; i < p.size(); i++)
	{
		for (int j=0;j<p[i].GetSizePro()/4;j++)
		{
			conOut(p[i].GetProY(j), p[i].GetProX(j) ) << p[i].GetFormaPro(j);
			if(VerifyRows(p[i].GetProX(j), 10, 10, nr,1)==4)
				conOut(p[i].GetProY(j), p[i].GetProX(j) - (VerifyRows(p[i].GetProX(j), 10, 10, nr,1) - 3)) << "  ";

			conOut(p[i].GetProY(j), p[i].GetProX(j) - (VerifyRows(p[i].GetProX(j), 10, 10, nr,1) + 1)) << "  ";
			p[i].SetProX(j,p[i].GetProX(j)+ VerifyRows(p[i].GetProX(j), 10, 10, nr,1));
			if (p[i].GetProX(j)+1 == nr)
			{
				conOut(p[i].GetProY(j), p[i].GetProX(j) -1) << "  ";

				p[i].ErasePro(j);
			}
		}
		//Sleep(50);
	}
	//std::this_thread::sleep_for(1s);
}

void CGame::PlanteP()
{
	static int ne = 0;

		for (int i = 0; i < SP.size(); i++)
		{
			if (SP[i].GetTimp() % 8 == 0&&ne!=timp.elapsedTime())
			{
				SP[i].SetProiectil();
				ne = timp.elapsedTime();
			}
		}
		static int ned = 0;
		for (int i = 0; i < DSP.size(); i++)
		{
			if (DSP[i].GetTimp() % 8 == 0&&ned!=timp.elapsedTime())
			{
				DSP[i].SetProiectil();
				ned = timp.elapsedTime();
			}
		}
		//if (timp.Mili()  > 8)
	//	{
			Afiseaza_Proiectile(SP, conOut, ter.Get_xrd());
			Afiseaza_Proiectile(DSP, conOut, ter.Get_xrd());
	//	}
}


template <typename T,typename G>
void Zombie_dem(vector <T> &zombie, vector <G> &DSP,int x, UserInterface::ConsoleOutput conOut)
{
	int k = 0;
	for (auto c = zombie.begin();c!=zombie.end();c++)
	{
		for (auto g=DSP.begin();g!=DSP.end();g++)
		{
			for (int i = 0; i <(*g).GetSizePro(); i++)
			{
				if ((*c).GetX() == (*g).GetProX(i) && (*c).GetY() == (*g).GetProY(i)||
					(*c).GetX() == ((*g).GetProX(i)-1) && (*c).GetY() == (*g).GetProY(i))
				{
					(*c).SetHeal((*c).GetHeal() - (*g).GetDemage(i));
					conOut((*g).GetProY(i), (*g).GetProX(i)-1) << "  ";
					(*g).ErasePro(i);

				}
			}
		}
		if ((*c).GetHeal() <= 0)
		{
			for (int i = (*c).GetY(); i < (*c).GetY() + 3; i++)
				for (int j = (*c).GetX(); j < (*c).GetX() + 3; j++)
					conOut(i, j) << "  ";
			zombie.erase(c);
			break;
		}

		if ((*c).GetX() == x + 1)
		{
			for (int i = (*c).GetY(); i < (*c).GetY() + 3; i++)
				for (int j = (*c).GetX(); j < (*c).GetX() + 3; j++)
					conOut(i, j) << "  ";
			zombie.erase(c);
			break;
		}

		
	}
}

template <typename T>
void Afisare_plante(vector <T> p,UserInterface::ConsoleOutput conOut, int n)
{
	int k = 0;
	for (auto &c : p)
	{
		k = 0;
		for (int i = c.GetY(); i < c.GetY() + 3; i++)
			for (int j = c.GetX(); j < c.GetX() + n; j++, k++)
				conOut(i, j) << c.GetForma()[k];
	}
}

template <typename T, typename G>
void Interactiune_Zombie_Plants(vector <T> &plants, vector <G> &zombie, int n,UserInterface::ConsoleOutput conOut)
{
	///for (auto a=plants.begin();a!=plants.end();a++)
	int k = 0;
	for(auto &a:plants)
	{
		//for (auto b = zombie.begin(); b != zombie.end(); b++)
		for (auto &b : zombie)
		{
			if (a.GetX() + 4 == b.GetX() && a.GetY() == b.GetY())
			{
				a.SetLife(a.Getlife() - b.GetDemage());
				b.SetMove(false);
			}
			if (a.Getlife() <= 0)
				b.SetMove(true);
			
		}
		
		if (a.Getlife() <= 0)
		{
			for (int i = a.GetY(); i <= a.GetY() + 2; i++)
				for (int j = a.GetX(); j <= a.GetX() + n; j++)
					conOut(i, j) << " ";
			plants.erase(plants.begin()+k);
		}
		k++;
	}
}

void CGame::ReSpawnPlants()
{
	Afisare_plante(DSP, conOut, 6);
	Afisare_plante(SP, conOut, 3);
	Afisare_plante(SF, conOut, 3);
	Afisare_plante(PP, conOut, 3);
	Afisare_plante(BP, conOut, 3);
	Interactiune_Zombie_Plants(PP, zombie, 3, conOut);
	Interactiune_Zombie_Plants(SF, zombie, 3, conOut);
	Interactiune_Zombie_Plants(SP, zombie, 3, conOut);
	Interactiune_Zombie_Plants(DSP, zombie, 6, conOut);
	Interactiune_Zombie_Plants(BP, zombie, 3, conOut);

}

void CGame::ZombieDemage()
{
	for (auto&c : zombie)
	{
		if (c.GetX() == 11)
		{
			finish++;
		}
		if (finish == 3)
		{
			endgame = true;
		}
	}
	Zombie_dem(zombie, DSP, ter.Get_xlu(),conOut);
	Zombie_dem(zombie, SP,ter.Get_xlu(),conOut);
}

void SunFlower_SunSpawn(UserInterface::ConsoleOutput conOut, vector <SunFlower> SF, vector <Sun> &sunny)
{
	int  k = 0;
	for (auto &c : SF)
	{
		if(c.GetTimp()%10==0&&c.GetDelay()!=c.GetTimp())
		{
			k = 0;
			Sun ssun;
			ssun.SetX(c.GetX() + 4);
			ssun.SetY(c.GetY());
			for (int i = ssun.GetY(); i < ssun.GetY() + 3; i++)
				for (int j = ssun.GetX(); j < ssun.GetX() + 3; j++, k++)
					conOut(i, j) << ssun.GetForma()[k];
			sunny.push_back(ssun);
			c.SetDelay(c.GetTimp());
		}
	}

}

void CGame::Start()
{
	afisare_teren();
	afisare_plante();
	while (!endgame)
	{
		//Sleep(100);
		Afisare_coord();
		if (timp.elapsedTime() % 15 == 0)
		SpawnZombie();
		if (timp.elapsedTime() % 20 == 0)
			SpawnZombieBucket();
		Afiseaza_Zombie();
		for (int i = 0; i < 100; i++)
		put_plants();
		if (timp.elapsedTime() % 15 == 0)
		SpawnSun();
		SunFlower_SunSpawn(conOut, SF, sun);
		ZombieDemage();
		CatchSun();
		ReSpawnPlants();
		PlanteP();
		AfiseazaPuncte();
		//std::this_thread::sleep_for(0.3s);
	}
	Afisare_Sfarsit(conOut);

}




int CGame::Chose()
{
	while (true)
	{

	Afisare_coord();
	if (conIn.coord.x > 71 && conIn.coord.x < 85)
	{
		system("cls");
		if (conIn.coord.y >= 12 && conIn.coord.y <= 14)
		{
			return 1;
		}
		if (conIn.coord.y >= 16 && conIn.coord.y <= 18)
		{
			return 2;
		}
		if (conIn.coord.y >= 20 && conIn.coord.y <= 22)
		{
			return 3;
		}
		if (conIn.coord.y >= 24 && conIn.coord.y <= 26)
		{
			exit(1);
			return 4;
		}

	}
	}

}


