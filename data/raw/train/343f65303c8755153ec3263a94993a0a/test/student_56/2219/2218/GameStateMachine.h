#pragma once
#include "Terrain.h"
#include "Missile.h"
#include "ZombiFactory.h"
#include "Resource.h"
#include <Windows.h>
#include "ConsoleOutput.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;
using namespace chrono;


class GameStateMachine
{

public:
	// Avem 5 secunde delay inainte ca un nou soare sa apara
	static const int TIME_BETWEEN_NEW_RESOURCES = 10000;

	//All the plants inside the game on the left side
	Terrain* m_terrain;

	//All the resources inside the application
	vector< Resource* > m_resources;

	// The available plants in the store
	vector<Plant*> m_availabale_plants;

	int m_resource_value = 50;

	int m_available_plant_selected = -1;

	bool need_refresh = false;

	chrono::high_resolution_clock::time_point time_resources;
public:
	GameStateMachine(int rows, int cols)
	{
		time_resources = chrono::high_resolution_clock::now();
		this->m_availabale_plants.push_back(new Peashooter());
		this->m_availabale_plants.push_back(new SunFlower());
		this->m_availabale_plants.push_back(new WallNut());
		m_terrain = new Terrain(rows, cols);
		if (cols == 1)
			ZombiFactory::Init(ZombiFactoryStrategy::INCREMENTAL_MORE,1);
		if (cols == 3)
			ZombiFactory::Init(ZombiFactoryStrategy::INCREMENTAL_MORE, 2);
		if (cols == 5)
			ZombiFactory::Init(ZombiFactoryStrategy::INCREMENTAL_MORE, 3);
	}

	Terrain* GetTerrain()
	{
		return this->m_terrain;
	}

	vector< Resource* >& GetResources()
	{
		return this->m_resources;
	}


	bool Update()
	{

		//UserInterface::ConsoleOutput::Refresh();
		auto new_time_update = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<milliseconds>(new_time_update - time_resources).count();
		
		// A trecut duration time de la ultima masurare.. trebuie sa actualizam state-ul jocului
		if (duration > TIME_BETWEEN_NEW_RESOURCES){
			Resource * s = new Sun();
			this->m_resources.push_back(move(s));
			time_resources = new_time_update;
		}
		auto zombi = ZombiFactory::CreateNewZombie();
		if (zombi != nullptr)
		{
			// if we really have a zombi need to put it on the terrain
			// for now let's choose one of the last lines which is not already busy
			int cols = this->m_terrain->Cols();
			int iter = 0;
			srand(time(NULL));
			while(iter < cols)
			{
			
				int _rand = rand() % cols;
				if ((*this->m_terrain)[this->m_terrain->Rows() - 1][_rand] == nullptr)
				{
					(*this->m_terrain)[this->m_terrain->Rows() - 1][_rand] = zombi;
					break;
				}
				iter++;
			}
		}
		// Check if the missile should be fired by the plants
		int cols = this->m_terrain->Cols();
		int rows = this->m_terrain->Rows();

		// Check if the plant should trigger his special efect
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if ((*this->m_terrain)[i][j] != nullptr && (*this->m_terrain)[i][j]->GetType() == 1)
					(*this->m_terrain)[i][j]->SpecialEfect();

		
		// if a missile is on the terrain check if this should be moved on
		// need to assign a given speed to each missile
		// let's say we want once half a second a given missile to be moved one line ahead
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if ((*this->m_terrain)[i][j] != nullptr)
				{
					// Avem cel putin o entitate
					if ((*this->m_terrain)[i][j]->GetType() == 2 && (*this->m_terrain)[i][j]->ShouldMoveOn() && i > 0)
					{
						if ((*this->m_terrain)[i - 1][j] != nullptr && (*this->m_terrain)[i -1][j]->GetType() == 1)
						{
							// Going back we found a plant ..let's damage it hihi
							auto damaged = (*this->m_terrain)[i - 1][j]->Damage();
							if (damaged)
							{
								(*this->m_terrain)[i - 1][j] = (*this->m_terrain)[i][j];
								(*this->m_terrain)[i][j] = nullptr;
								(*this->m_terrain)[i - 1][j]->Clear();
								if (i - 1 == 0)
								{
									system("cls");
									cout << "Game Over";
									return false;
								}
							}
						}
						else
						{
							// simply move on
							(*this->m_terrain)[i - 1][j] = (*this->m_terrain)[i][j];
							(*this->m_terrain)[i][j] = nullptr;
							(*this->m_terrain)[i - 1][j]->Clear();
							if (i - 1 == 0)
							{
								system("cls");
								cout << "Game Over";
								return false;
							}
						}
						// Ea este zombi. Zombi trb sa se miste inapoi
				
					}
					else if ((*this->m_terrain)[i][j]->GetType() == 3)
					{
						if (i == rows - 1)
						{
							// need to clear it
							(*this->m_terrain)[i][j]->Clear();
							//delete (*this->m_terrain)[i][j];
							(*this->m_terrain)[i][j] = nullptr;
						}
						// Ea este missile.
						else if ((*this->m_terrain)[i][j]->ShouldMoveOn())
						{
							// Next field is zombi
							if ((*this->m_terrain)[i + 1][j]!= nullptr && (*this->m_terrain)[i + 1][j]->GetType() == 2)
							{
								// Damage the zombi
								auto damaged = (*this->m_terrain)[i + 1][j]->Damage();
								// Check if the zombi si damaged
								if (damaged)
								{
									(*this->m_terrain)[i + 1][j]->Clear();
									//delete (*this->m_terrain)[i + 1][j];
									(*this->m_terrain)[i + 1][j] = nullptr;

								}
								// Clear the missile
								(*this->m_terrain)[i][j]->Clear();
								//delete (*this->m_terrain)[i][j];
								(*this->m_terrain)[i][j] = nullptr;
							}
							else
							{
								(*this->m_terrain)[i + 1][j] = (*this->m_terrain)[i][j];
								(*this->m_terrain)[i][j] = nullptr;
								(*this->m_terrain)[i + 1][j]->Clear();
							}
						
						}
					}
				}
			}
		}

		return true;
	}

	Resource* ResourceRef(int index)
	{
		return m_resources[index];
	}
	
	bool ExistResource(int index)
	{
		return index <= ResourceSize() - 1;
	}
	
	int DeleteResource(int index)
	{
		if (ExistResource(index))
		{
			int value = this->ResourceRef(index)->Value();
			this->m_resources.erase(this->m_resources.begin() + index);
			return value;
		}
		return 0;
	}

	int ResourceSize() const
	{
		return this->m_resources.size();
	}

	void AddResourceValue(int value)
	{
		this->m_resource_value += value;
	}

	int ResourceValues()
	{
		return this->m_resource_value;
	}

	void DrawAvailablePlants()
	{		
		for (int i = 0; i < this->m_availabale_plants.size(); i++) {
			this->m_availabale_plants[i]->Draw(
				2 * Utils::THREESHOLD_BETWEEN_COMPONENTS + Utils::THREESHOLD_BETWEEN_SQUARES + Utils::SCOREBOARD_WIDTH + i * Utils::PLANT_SQUARE_DIM,
				Utils::THREESHOLD_BETWEEN_SQUARES,
				2 * Utils::THREESHOLD_BETWEEN_COMPONENTS + Utils::THREESHOLD_BETWEEN_SQUARES + Utils::SCOREBOARD_HEIGHT - 40 + (i + 1) * Utils::PLANT_SQUARE_DIM,
				Utils::THREESHOLD_BETWEEN_SQUARES + Utils::SCOREBOARD_HEIGHT - 40,true);
		}
	}

	void DrawTerrain()
	{
		this->m_terrain->Draw(
			Utils::SCOREBOARD_WIDTH + Utils::THREESHOLD_BETWEEN_COMPONENTS,
			Utils::SCOREBOARD_HEIGHT + Utils::THREESHOLD_BETWEEN_COMPONENTS,
			Utils::PLANTS_NUM_SLOTS * (Utils::THREESHOLD_BETWEEN_SQUARES + Utils::PLANT_SQUARE_DIM),
			Utils::SCOREBOARD_HEIGHT + Utils::THREESHOLD_BETWEEN_COMPONENTS + Utils::SUN_NUM_SLOTS * (Utils::SUN_SQUARE_DIM +
				Utils::THREESHOLD_BETWEEN_SQUARES));


	}

	void SelectPlant(int index)
	{
		this->m_available_plant_selected = index;
	}

	void AddPlantToTerrain(int x, int y)
	{
		if (m_available_plant_selected == -1) return;
		if (m_available_plant_selected > m_availabale_plants.size()) return;
		int cost_plant = m_availabale_plants[m_available_plant_selected]->GetCost();
		if (cost_plant > this->m_resource_value)//
			return;

		// Verify if the plant need to recharg
		
		auto plant = m_availabale_plants[m_available_plant_selected];
		plant->SetContext(x, y, this);

		(*this->m_terrain)[x][y] = plant->Copy();

		this->m_resource_value -= cost_plant;
		this->m_available_plant_selected = -1;
		// Need to put the plant on terrain

	}

	bool NeedRefresh()
	{
		return this->need_refresh;
	}

};

