#pragma once
#pragma once
#include "TerrainEntity.h"
#include "Utils.h"

class Zombi : public TerrainEntity
{
protected:
	/// The speed of the zombie.How many quantes of time need to advance one square
	int m_speed;

	// proportional with number of given proiectile to die
	int m_strength; 

public:
	// Base zombi doesn't need to display it on the terrain
	virtual string GetName()  const = 0;

	virtual int GetType() const = 0;

	virtual int GetSpeed() const = 0;

	bool virtual IsReady() { return true; }
};

class BasicZombi : public Zombi {

protected:
	int m_damage = 5;
public:

	// Base zombi doesn't need to display it on the terrain
	virtual string GetName()  const
	{
		return "BZ";
	}
	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect = false) override
	{
		TerrainEntity::Draw(x1 + 80, y1 + 70, x2, y2);
		Utils::BCX_DrawNumber_Console(x1 + 80, y1 + 70 , GetName());
	}

	virtual int GetType() const
	{
		return 2;
	}
	virtual int GetSpeed() const
	{
		return 1;
	}

	virtual bool Damage()
	{
		this->m_damage--;
		if (this->m_damage <= 0)
			return true;
		return false;
	}
	virtual TerrainEntity* Copy()
	{
		return new BasicZombi();
	}
};

class BuckedHeadZombi : public BasicZombi {

protected:
	int m_damage = 10;//de 2 ori mai rezistent decat basic
public:

	// Base zombi doesn't need to display it on the terrain
	virtual string GetName()  const
	{
		return "BHZ";
	}
	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect = false) override
	{
		TerrainEntity::Draw(x1 + 80, y1 + 70, x2, y2);
		Utils::BCX_DrawNumber_Console(x1 + 80, y1 + 70, GetName());
	}

	virtual int GetType() const
	{
		return 2;
	}
	virtual int GetSpeed() const
	{
		return 1;
	}

	virtual bool Damage()
	{
		this->m_damage--;
		if (this->m_damage <= 0)
			return true;
		return false;
	}
	virtual TerrainEntity* Copy()
	{
		return new BuckedHeadZombi();
	}
};

class PoleVaultingZombi : public BasicZombi {

protected:
	int m_damage = 5;
public:

	// Base zombi doesn't need to display it on the terrain
	virtual string GetName()  const
	{
		return "PVZ";
	}
	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect = false) override
	{
		TerrainEntity::Draw(x1 + 80, y1 + 70, x2, y2);
		Utils::BCX_DrawNumber_Console(x1 + 80, y1 + 70, GetName());
	}

	virtual int GetType() const
	{
		return 2;
	}
	virtual int GetSpeed() const
	{
		return 2;//marire viteza o unitate
	}

	virtual bool Damage()
	{
		this->m_damage--;
		if (this->m_damage <= 0)
			return true;
		return false;
	}
	virtual TerrainEntity* Copy()
	{
		return new PoleVaultingZombi();
	}
};