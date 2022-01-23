#pragma once
#include "IDrawable.h"
#include <string>
#include "Utils.h"
using namespace std;
class TerrainEntity : public IDrawable
{
protected:
	int Update_Cycle = 0;
	RECT m_rectange = { 0,0,0,0 };
	POINT p;
	int x1; int y1;
public:
	// Draw the object at specific coordinates on the Console Handle
	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect = false) override
	{
		p = { x1,y1};
		this->x1 = x1;
		this->y1 = y1;
		RECT r;
		auto hwnd = WindowFromPoint(p);
		GetWindowRect(hwnd, &r);
		Update_Cycle++;
		m_rectange = r;
	}

	virtual void Clear()
	{
	
		Utils::BCX_DrawNumber_Console(this->x1,this->y1, "     ");
	}
	virtual TerrainEntity* Copy() = 0;
	 //Get the visual name which appears on the terrain eg: P - for simple Peashooter
	virtual string GetName() const = 0;

	// Return the type of entity
	// 1 - plant
	// 2 - zombi
	// 3 - missle
	virtual int GetType() const = 0;

	// Returns the speed of the entity
	virtual int GetSpeed() const = 0;

	// This function is being triggered at each step.
	// Based on speed the entity should decide if it should advance
	virtual bool ShouldMoveOn()
	{
		int my_speed = GetSpeed();
		if (my_speed == 0)
			return false;
		auto speed_thresshold = Utils::THREESHOLD_SPEED_MOVING;
		int update_period = speed_thresshold / my_speed;

		if (Update_Cycle > update_period)
		{
			Update_Cycle = 0;
			return true;
		}
		return false;

	}

	//true if the entity is ready to do any operation, eg : plants to shout
	bool virtual IsReady() = 0;

	/// Damage the entity. Returns the true if the entity is destroyed 
	/// The caller should clear the entity after is being distoryed
	virtual bool Damage() = 0;

	virtual void SpecialEfect() {};
};

