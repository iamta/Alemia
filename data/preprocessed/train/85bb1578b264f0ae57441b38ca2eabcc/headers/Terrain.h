#pragma once
#include "TerrainEntity.h"
#include "Plant.h"
#include <vector>
#include <string>
#include <time.h>
#include <chrono>
using namespace std;
using namespace chrono;

class Terrain : public IDrawable
{
protected:
	int m_rows;

	int m_columns;

	using  arrayEntities = std::vector<TerrainEntity*>;

	std::vector<arrayEntities> m_entities;
public:
	Terrain(int rows, int columns);
	
	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect = true) override;

	virtual void Clear() {}

	std::vector < TerrainEntity*>& operator[](int index)
	{
		return this->m_entities[index];
	}

	int Rows() { return this->m_rows; }

	int Cols() { return this->m_columns; }

};

