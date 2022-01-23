#pragma once
#include "TerrainEntity.h"
#include "Utils.h"

class Missile : public TerrainEntity
{

public:

	virtual string GetName()  const = 0;

	virtual int GetType() const = 0;

	virtual int GetSpeed() const
	{
		return 55;
	}

	bool virtual IsReady() { return true; }


};

class SimpleMissile : public Missile
{

public:

	virtual void Draw(int x1, int y1, int x2, int y2, bool unused) override
	{
		TerrainEntity::Draw(x1 + 70, y1 + 70, x2, y2);
		Utils::BCX_DrawNumber_Console(x1 + 70, y1 + 70, GetName());
	}
	virtual string GetName()  const
	{
		return "*****";
	}

	virtual int GetType() const
	{
		return 3;
	}
	virtual bool Damage()
	{
		return false;
	}
	virtual TerrainEntity* Copy()
	{
		return new SimpleMissile();
	}
};
