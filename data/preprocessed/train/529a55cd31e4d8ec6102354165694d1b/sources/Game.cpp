#include "Game.h"
#include <windows.h>
#include <cstdlib>
#include <iostream>
using namespace std;

//void Game::Start()
//{
//	this->m_allowed_actions.push_back(Operation::Idle);
//	this->m_allowed_actions.push_back(Operation::Click);
//}
//
//Game::Game(string n_name, int rows, int columns)
//{
//	this->m_name = n_name;
//	this->m_columns = columns;
//	this->m_rows = rows;
//	this->m_game_state_machine = new GameStateMachine(rows, columns);
//
//}
//
//void Game::Update(UserAction new_action)
//{
//	if (new_action.GetOperation() == Operation::Click){
//		float x = atof(new_action[0].c_str());
//		float y = atof(new_action[1].c_str());
//
//		HWND console_handle = GetConsoleWindow();
//		const auto context = GetDC(console_handle);
//
//		POINT p = { x,y };
//		RECT r;
//		auto hwnd = WindowFromPoint(p);
//		GetWindowRect(hwnd, &r);
//
//		// coordonatele sunt diferite rau hack
//		int dim_x = x * 10;
//		int dim_y = y * 20;	
//		
//		// TODO validate that the coordinates are ok
//		if  (dim_y <= Utils::SCOREBOARD_WIDTH && dim_x >= Utils::SCOREBOARD_HEIGHT &&
//			dim_x < Utils::PLANTS_NUM_SLOTS * (  Utils::THREESHOLD_BETWEEN_SQUARES* Utils::PLANT_SQUARE_DIM))
//		{
//			
//			int index = dim_x / (Utils::THREESHOLD_BETWEEN_SQUARES +  Utils::PLANT_SQUARE_DIM + Utils::SCOREBOARD_WIDTH);
//			int value = this->m_game_state_machine->DeleteResource(index);
//		
//		
//
//			//RECT rect = { dim_x,dim_x + dim_y,dim_y,dimy };
//
//			// Collect new value 
//			this->m_game_state_machine->AddResourceValue(value);
//					
//			//InvalidateRect(console_handle, &r, TRUE);
//			//UpdateWindow(console_handle);
//		}
//		// TODO detect plant corrected
//		
//		if (dim_y >= Utils::SCOREBOARD_WIDTH && dim_x <= Utils::SCOREBOARD_HEIGHT)
//		{
//			int index = dim_y / (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM + Utils::SCOREBOARD_WIDTH);
//			this->m_game_state_machine->SelectPlant(index);
//
//		}
//		if (dim_y >= Utils::SCOREBOARD_WIDTH && dim_x >= Utils::SCOREBOARD_HEIGHT && 
//			dim_x < Utils::PLANTS_NUM_SLOTS * (Utils::THREESHOLD_BETWEEN_SQUARES * Utils::PLANT_SQUARE_DIM))
//		{
//			int _x = (dim_x - Utils::SCOREBOARD_WIDTH) / (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM);
//			int _y = (dim_y - Utils::SCOREBOARD_WIDTH) / (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM);
//			this->m_game_state_machine->AddPlantToTerrain(_x, _y);
//
//			//InvalidateRect(console_handle, &r, TRUE);
//			//UpdateWindow(console_handle);
//
//		}
//	}
//	// a mai trecut o cuanta de timp randam scena
//	RenderScene();
//
//}
//
//void Game::RenderScene()
//{
//	// Apelam desenele
//
//	this->m_game_state_machine->Update();
//	
//	HWND console_handle = GetConsoleWindow();
//	const auto context = GetDC(console_handle);
//
//	this->m_game_state_machine->DrawAvailablePlants();
//
//	this->m_game_state_machine->DrawTerrain();
//
//}

void ConsoleGame::Start()
{
	this->m_allowed_actions.push_back(Operation::Idle);
	this->m_allowed_actions.push_back(Operation::Click);
}

ConsoleGame::ConsoleGame(string n_name, int rows, int columns)
{
	this->m_name = n_name;
	this->m_columns = columns;
	this->m_rows = rows;
	this->m_game_state_machine = new GameStateMachine(rows, columns);
	if (columns == 1)
		m_level = 1;
	if (columns == 3)
		m_level = 2;
	if (columns == 5)
		m_level = 3;

}

bool ConsoleGame::Update(UserAction new_action)
{
	if (new_action.GetOperation() == Operation::Click) {
		float x = atof(new_action[0].c_str());
		float y = atof(new_action[1].c_str());

		HWND console_handle = GetConsoleWindow();
		const auto context = GetDC(console_handle);

		POINT p = { x,y };
		RECT r;
		auto hwnd = WindowFromPoint(p);
		GetWindowRect(hwnd, &r);

		// coordonatele sunt diferite rau hack
		int dim_x = x * 10;
		int dim_y = y * 20;

		// TODO validate that the coordinates are ok
		if (dim_y <= Utils::SCOREBOARD_WIDTH && dim_x >= Utils::SCOREBOARD_HEIGHT &&
			dim_x < Utils::PLANTS_NUM_SLOTS * (Utils::THREESHOLD_BETWEEN_SQUARES * Utils::PLANT_SQUARE_DIM))
		{

			int index = (dim_x - Utils::SCOREBOARD_WIDTH - Utils::THREESHOLD_BETWEEN_COMPONENTS) / (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM);
			int value = this->m_game_state_machine->DeleteResource(index);
			// Collect new value 
			this->m_game_state_machine->AddResourceValue(value);

			// Hack refresh
			Utils::BCX_Clear(
				Utils::THREESHOLD_BETWEEN_COMPONENTS,
				Utils::SCOREBOARD_HEIGHT + 2 * Utils::THREESHOLD_BETWEEN_COMPONENTS + index * Utils::SUN_SQUARE_DIM,
				Utils::SUN_SQUARE_DIM - Utils::THREESHOLD_BETWEEN_COMPONENTS - 20,
				Utils::SCOREBOARD_HEIGHT + 2 * Utils::THREESHOLD_BETWEEN_COMPONENTS + (index + 1) * Utils::SUN_SQUARE_DIM - 4);

		}
		// TODO detect plant corrected

		if (dim_y >= Utils::SCOREBOARD_WIDTH && dim_x <= Utils::SCOREBOARD_HEIGHT)
		{
			int index = (dim_y - Utils::SCOREBOARD_WIDTH - Utils::THREESHOLD_BETWEEN_COMPONENTS) / (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM);
			this->m_game_state_machine->SelectPlant(index);

		}
		if (dim_y >= Utils::SCOREBOARD_WIDTH && dim_x >= Utils::SCOREBOARD_HEIGHT &&
			dim_x < Utils::PLANTS_NUM_SLOTS * (Utils::THREESHOLD_BETWEEN_SQUARES * Utils::PLANT_SQUARE_DIM))
		{
			int _x = (dim_x - Utils::SCOREBOARD_WIDTH) / (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM);
			int _y = (dim_y - Utils::SCOREBOARD_WIDTH) / (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM);
			this->m_game_state_machine->AddPlantToTerrain(_x, _y);

		}
	}
	return RenderScene();
}
bool ConsoleGame::RenderScene()
{
	// Aici trebuie sa desenam

	auto response = this->m_game_state_machine->Update();
	if (!response)
		return false;

	HWND console_handle = GetConsoleWindow();
	const auto context = GetDC(console_handle);



	// Draw the resources vales
	string s = to_string(this->m_game_state_machine->ResourceValues());
	Utils::BCX_DrawNumber_Console(55, 45, "   ");
	Utils::BCX_DrawNumber_Console(55, 45, s);


	// Desenam scoare boardul 
	Utils::BCX_Rectangle_Console(0, 0, Utils::SCOREBOARD_HEIGHT, Utils::SCOREBOARD_HEIGHT);

	Utils::BCX_Rectangle_Console(0,Utils::SCOREBOARD_HEIGHT + Utils::THREESHOLD_BETWEEN_COMPONENTS,
		Utils::SUN_HEADER_HEIGHT,
		Utils::SCOREBOARD_HEIGHT +
		Utils::THREESHOLD_BETWEEN_COMPONENTS +
		Utils::SUN_NUM_SLOTS * (Utils::SUN_SQUARE_DIM + Utils::THREESHOLD_BETWEEN_SQUARES));

	for (int i = 0; i < Utils::SUN_NUM_SLOTS; i++) {
		bool Fill = false;
		if (this->m_game_state_machine->ExistResource(i))
			Fill = true;
		Utils::BCX_Rectangle_Console(
		    Utils::THREESHOLD_BETWEEN_COMPONENTS, 
			Utils::SCOREBOARD_HEIGHT +  2 * Utils::THREESHOLD_BETWEEN_COMPONENTS + i * Utils::SUN_SQUARE_DIM,
			Utils::SUN_SQUARE_DIM - Utils::THREESHOLD_BETWEEN_COMPONENTS - 20,
			Utils::SCOREBOARD_HEIGHT + 2 * Utils::THREESHOLD_BETWEEN_COMPONENTS + (i + 1) * Utils::SUN_SQUARE_DIM - 4,
			Fill);
	}

	//// desenam dreptunghiul cu plante
	Utils::BCX_Rectangle_Console(
		Utils::SCOREBOARD_WIDTH + Utils::THREESHOLD_BETWEEN_COMPONENTS,
		0,
		Utils::PLANTS_NUM_SLOTS *
		(Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM),
		Utils::SUN_HEADER_HEIGHT);
		


	this->m_game_state_machine->DrawAvailablePlants();

	this->m_game_state_machine->DrawTerrain();

	return true;

}