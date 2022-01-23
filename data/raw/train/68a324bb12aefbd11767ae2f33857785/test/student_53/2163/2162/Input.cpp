#include "Input.h"



Input::Input()
{
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(hStdin, fdwMode);
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, fdwMode);
	isSelected = 0;
	hold = 0;
}

void Input::print_mouse()
{
	DWORD nr = 0;
	GetNumberOfConsoleInputEvents(hStdin, &nr);
	if (nr)
	{
		ReadConsoleInput(hStdin,  irInBuf,  128,   &cNumRead); 
		mouse_pos = { irInBuf[0].Event.MouseEvent.dwMousePosition.X ,irInBuf[0].Event.MouseEvent.dwMousePosition.Y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
		std::cout << irInBuf[0].Event.MouseEvent.dwMousePosition.X << " " << irInBuf[0].Event.MouseEvent.dwMousePosition.Y;
		std::cout << "						";
	}
}


DWORD Input::get_mouse_botton_state(MOUSE_EVENT_RECORD ir)
{
	return ir.dwButtonState;
}

bool Input::select(PlantList& e,SunList& Floare,Money &money,BulletList&gloante,Logfile&L)
{
		Entity **list = e.get_vector();
		for (int i = 0; i < 5; i++)
		{
			COORD aux = list[i]->get_entity_pos();

			if ((aux.X + 2 >= mouse_pos.X  && aux.X - 2 <= mouse_pos.X) && (aux.Y + 2 >= mouse_pos.Y  && aux.Y - 2 <= mouse_pos.Y))
			{
				int& income = money.get_money();
				if (income>=list[i]->get_cost())
				{
					if ((get_mouse_botton_state(irInBuf[0].Event.MouseEvent) == FROM_LEFT_1ST_BUTTON_PRESSED))
					{
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,2 });
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
						
						std::cout << "The object was selected    ";
						std::cout << i;
						if (hold == 0)
						{
							std::string str = "A fost selectata planata cu numarul ";//ggjhgjhg
							str += to_string(i);
							L.get_user_action(str);
						}
						check_if_sunflower(i,Floare);

						if(hold==0)
						income = income - list[i]->get_cost();//!!!!!!!!!! La costuri face mai mult decat trebuie;
					

						money.sterge_money();
						money.print_money();

						temp = e.get_temp(i);

						if (i == 0)
						{
							TempBul = new Bullet_normal(20,temp->get_entity_pos(),'>');
							gloante.add_bullet_type_to_list(i);
						}
						else if(i==4)
						{
							TempBul = new Bullet_frozen(2000,temp->get_entity_pos(),'*');
							gloante.add_bullet_type_to_list(i);
						}

						isSelected = 1;
						hold = 1;
						
						return true;
					}
				}
			}
		}
		Sun *Sori = Floare.get_Sori();
		
			for (int i = 0; i < 9; i++)
			{

				COORD aux = Sori[i].get_coord();
				int exist = Sori[i].get_selcted();
				if ((aux.X + 2 >= mouse_pos.X  && aux.X - 2 <= mouse_pos.X) && (aux.Y + 2 >= mouse_pos.Y  && aux.Y - 2 <= mouse_pos.Y) && exist == 1)
				{
					if ((get_mouse_botton_state(irInBuf[0].Event.MouseEvent) == FROM_LEFT_1ST_BUTTON_PRESSED))
					{

						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,1 });
						std::cout << "							";
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,1 });
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

						L.get_user_action("The Sun was colected");

						std::cout << "The Sun was colected";
						std::cout << i;
						money.sterge_money();
						money.increase_money();
						money.print_money();
						Sori[i].set_selected(0);
						Sori[i].sterge();
						return true;

					}
				}
			}
		
	return false;
}

void Input::deselect(Grid &G,PlantList &e,BulletList & B, Logfile&L)
{
	if (irInBuf[0].Event.MouseEvent.dwEventFlags == MOUSE_MOVED && isSelected == 1)
	{
		isSelected = 0;
		return;
	}
	else if (irInBuf[0].Event.MouseEvent.dwEventFlags == MOUSE_MOVED && isSelected == 0)
	{
		return;
	}
	if (isSelected == 0&&hold==1)
	{
			if ((get_mouse_botton_state(irInBuf[0].Event.MouseEvent) == FROM_LEFT_1ST_BUTTON_PRESSED))
			{
				if (snap_tool_grid(G, e) == true)
				{
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,2 });
					std::cout << "										";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,2 });
					//jhghjgh
					std::string str = "A fost plasata planata la pozitia ";
					std::string aux = to_string(mouse_pos.X);
					aux += "		";
					aux += to_string(mouse_pos.Y);
					str += aux;
					L.get_user_action(str);

					std::cout << "The object was deselected";
					e.put_it_inside(temp);
					e.update_curent_object(mouse_pos);
					e.print_curent_object();
					e.increase_contor();
					if (TempBul != NULL)
					{
						TempBul->set_bullet_pos(mouse_pos);
						B.add_bulet_to_list(TempBul);
						B.increase_contor();
						TempBul = NULL;
					}
					temp = NULL;
					isSelected = 1;
					hold = 0;
				}
			}
	}
}

void Input::check_if_sunflower(int i,SunList&Floare)
{
	if (i ==1)
	{
		int &time = Floare.get_remember();
		time += 10000;
	}
}

bool Input::snap_tool_grid(Grid & G, PlantList & e)
{
	vector<Block> M = G.get_cage();
	for (int i = 0; i < 45; i++)
	{
		COORD X = M[i].get_mijloc();
		if ((X.X + 4 >= mouse_pos.X  && X.X - 4 <= mouse_pos.X) && (X.Y + 2 >= mouse_pos.Y  && X.Y - 2 <= mouse_pos.Y))
		{
			mouse_pos.X = X.X;
			mouse_pos.Y = X.Y;
			M[i].change_mijloc(temp->get_char());
			return true;
		}
	}
	return false;
}

Input::~Input()
{
}
