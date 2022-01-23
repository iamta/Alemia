#include "Terrain.h"
#include<iostream>


Terrain::Terrain(int rows, int columns)
{
	this->m_columns = columns;
	this->m_rows = rows;
	for (int i = 0; i < rows; i++)
	{
		this->m_entities.push_back(std::vector<TerrainEntity*>(columns));
	}
}

void Terrain::Draw(int x1, int y1, int x2, int y2, bool DrawRect)
{
	if ( DrawRect == true)
		Utils::BCX_Rectangle_Console(x1,y1,x2,y2);

	// desenam terenul
	for (int i = 0; i < this->m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {


			Utils::BCX_Rectangle_Console(
				2 * Utils::THREESHOLD_BETWEEN_COMPONENTS + Utils::THREESHOLD_BETWEEN_SQUARES + Utils::SCOREBOARD_WIDTH + j * Utils::PLANT_SQUARE_DIM,
				Utils::THREESHOLD_BETWEEN_COMPONENTS  + Utils::THREESHOLD_BETWEEN_SQUARES + Utils::SCOREBOARD_HEIGHT + i * Utils::PLANT_SQUARE_DIM,
				2 * Utils::THREESHOLD_BETWEEN_COMPONENTS  + Utils::SCOREBOARD_WIDTH + (j + 1) * Utils::PLANT_SQUARE_DIM,
				Utils::THREESHOLD_BETWEEN_COMPONENTS  + Utils::SCOREBOARD_HEIGHT + (i + 1) * Utils::PLANT_SQUARE_DIM);
				;

			if (this->m_entities[i][j] != nullptr)
			{
				if (this->m_entities[i][j]->GetType() == 1)
					std::cout << " ";
				this->m_entities[i][j]->Draw(
					Utils::THREESHOLD_BETWEEN_SQUARES + Utils::SCOREBOARD_WIDTH + (j) * Utils::PLANT_SQUARE_DIM,
					Utils::THREESHOLD_BETWEEN_SQUARES + Utils::SCOREBOARD_HEIGHT + i * Utils::PLANT_SQUARE_DIM,
					Utils::SCOREBOARD_WIDTH + (j + 1) * Utils::PLANT_SQUARE_DIM,
					Utils::SCOREBOARD_HEIGHT + (i + 1) * Utils::PLANT_SQUARE_DIM);
			}

		}
	}
}