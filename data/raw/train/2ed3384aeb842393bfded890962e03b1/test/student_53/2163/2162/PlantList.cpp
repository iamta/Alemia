#include "PlantList.h"



PlantList::PlantList()
{
	for (int i = 0; i < 100; i++)
	{
		active_plants[i] = nullptr;
	}
	vector[0] = new Peashooter;
	vector[1] = new Sunflower;
	vector[2] = new Chery_Bomb;
	vector[3] = new Wall_nut;
	vector[4] = new Snow_pea;
	CB_index = 0;
}

void PlantList::get_plant(int i)
{
	
		switch (i)
		{
		case 0:
			active_plants[contor] = new Peashooter();
			break;
		
		case 1:
			active_plants[contor] = new Sunflower();
			break;
			
		case 2:
			active_plants[contor] = new Chery_Bomb();
			CB_index = 1;
			break;
		
		case 3:
			active_plants[contor] = new Wall_nut();
			break;
		
		case 4:
			active_plants[contor] = new Snow_pea();
			break;
			
		default:
			break;
		}
	
		if (contor > 46)
		{
			throw Exception(0);
		}
}

Entity* PlantList::get_temp(int i)
{
	switch (i)
	{
	case 0:
		return new Peashooter();
		break;

	case 1:
		return new Sunflower();
		break;

	case 2:
		return new Chery_Bomb();
		break;

	case 3:
		return  new Wall_nut();
		break;

	case 4:
		return new Snow_pea();
		break;

	default:
		break;
	}
}

void PlantList::put_it_inside(Entity * temp)
{
	active_plants[contor] = temp;
	
}

void PlantList::print()
{
	for (int i = 0; i < 5; i++)
	{
		vector[i]->print();
		COORD pos = vector[i]->get_entity_pos();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { pos.X,pos.Y + 1 });
		cout << vector[i]->get_cost();
		
	}
}

void PlantList::update_curent_object(COORD mouse_pos)
{
	std::cout <<endl <<contor<<"       "<<mouse_pos.X<<"    "<<mouse_pos.Y;
	if (active_plants[contor] != nullptr)
		active_plants[contor]->set_pos(mouse_pos);

}

void PlantList::print_curent_object()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	if (active_plants[contor] != nullptr)
	active_plants[contor]->print();

}

void PlantList::update_active_plants(int i)
{
	active_plants[i] = NULL;
}


PlantList::~PlantList()
{
}
