#include "GameStateMachine.h"


// Circular Dependency. All methods with game state machine put here
Peashooter::Peashooter(int x1, int y1, GameStateMachine* game)
{
	this->x = x1;
	this->y = y1;
	this->pInstanceStateMachine = game;
}

void Plant::SetContext(int x1, int y1, GameStateMachine* pInstance) 
{
	this->x = x1;
	this->y = y1;
	this->pInstanceStateMachine = pInstance;
}

void Peashooter::SpecialEfect()
{
	auto terrain = this->pInstanceStateMachine->GetTerrain();
	auto rows = terrain->Rows();
	auto cols = terrain->Cols();
	auto i = this->x;
	auto j = this->y;

	for (int k = i + 1; k < rows; k++)
		if ((*terrain)[k][j] != nullptr)
		{
			if ((*terrain)[k][j]->GetType() == 2 && (*terrain)[i][j]->IsReady())
			{
				// put one missile on the next line
				if ((*terrain)[i + 1][j] != nullptr)
				{
					if ((*terrain)[i + 1][j]->GetType() == 2)
					{
						auto damaged = (*terrain)[i + 1][j]->Damage();
						if (damaged)
						{
							(*terrain)[i + 1][j]->Clear();
							//delete (*terrain)[i + 1][j];
							(*terrain)[i + 1][j] = nullptr;
						}
					}
				}
				else
				{
					(*terrain)[i + 1][j] = new SimpleMissile();
				}
				break;
			}
		}
}

void SunFlower::SpecialEfect()
{
	if (this->IsReady())
	{
		Resource* s = new Sun();
		auto& resources = this->pInstanceStateMachine->GetResources();
		resources.push_back(move(s));
	}
}