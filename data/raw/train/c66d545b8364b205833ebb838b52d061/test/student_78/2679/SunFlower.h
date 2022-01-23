#pragma once

#include "Plant.h"
#include "IDrawable.h"

class SunFlower :
	public Plant
{
public:

	SunFlower(int a, int b) :Plant(a, b, 50, 3, 10) { plantType = Plant::PlantType::Sunflower; }
	~SunFlower();

	int getX() override { return this->getx(); };
	Plant* clone() { return new SunFlower(*this); }
	void draw() override;
	void update()override;
};

