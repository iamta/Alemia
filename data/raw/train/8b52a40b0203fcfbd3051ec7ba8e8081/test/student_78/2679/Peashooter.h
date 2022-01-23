#pragma once

#include "Plant.h"
#include "IDrawable.h"

class Peashooter :
	public Plant
{
public:

	Peashooter(int x, int y) :Plant(x, y, 100, 3, 5) { plantType = Plant::PlantType::Peashooter; };
	~Peashooter();

	int getX() override { return this->getx(); };
	Plant* clone() { return new Peashooter(*this); }
	void draw() override;
	void update()override;

};

