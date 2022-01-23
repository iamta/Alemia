#pragma once
#include "TerrainEntity.h"
#include "Utils.h"

class GameStateMachine;

// clas abstracta pt toate plantele
class Plant : public TerrainEntity
{
protected:
	//cost pentru a o planta
	int m_cost;
	// nr maxim de muscauri
	int m_max_bytes;
	// daca este plantata
	int is_planted;
	//salvam si timpul plantarii sa 
	int time_planted;
	// position in terrain
	int x;
	// position in terrain
	int y;

	/// Pointer to the game state machine
	GameStateMachine* pInstanceStateMachine;

public:
	virtual int GetTime() = 0;
	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect=false) = 0;
	virtual int GetCost() const = 0;
	virtual string GetName() const = 0;
	virtual int GetType() const = 0;
	virtual int GetSpeed() const 
	{ 
		return 0; 
	}
	virtual void SetContext(int x1, int y1, GameStateMachine* pInstance);

};

class SunFlower : public Plant
{
	int m_damage = 5;
	int Threeshold_Shot = 100;
public:

	// Asteptam 5 secunde ca sa plantamm o noua planta de tipul acesta
	virtual int GetTime()
	{
		return 5;
	}
	virtual string GetName() const override
	{
		return "SnF";
	}

	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect)
	{
		TerrainEntity::Draw(x1, y1, x2, y2);
		if (DrawRect == true)
		{
			Utils::BCX_Rectangle_Console(x1, y1, x2, y2);
			Utils::BCX_DrawNumber_Console(x1 + 45, y1 + 35, GetName());
		}
		else
		{
			Utils::BCX_DrawNumber_Console(x1 + 80, y1 + 70, GetName());
		}
	}

	virtual int GetCost() const
	{
		return 50;
	}

	//  nu e pa....
	virtual int GetType() const
	{
		return 1;
	}

	// Daca este muscata decrementam un pic. 5 muscaturi maxim
	virtual bool Damage()
	{
		this->m_damage--;
		if (this->m_damage <= 0)
			return true;
		return false;
	}

	bool virtual IsReady()
	{
		//daca e ready da soare
		if (this->Update_Cycle % Threeshold_Shot == 0)
		{
			return true;
		}
		return false;
	}
	virtual void SpecialEfect() override;

	virtual TerrainEntity* Copy()
	{
		auto sun = new  SunFlower();
		sun->x = this->x;
		sun->y = this->y;
		sun->pInstanceStateMachine = this->pInstanceStateMachine;
		return sun;
	}
};


class Peashooter : public Plant
{
	// Trebuie sa salvam si cand a tras ultima data sa nu traga la infinit...punem delay-uri intre trageri
	int Threeshold_Shot = 15;
	// Poate fi mancata de maxim 5 ori 
	int m_damage = 5;
public:
	Peashooter(int x1, int y1, GameStateMachine* game);

	// Asteptam 5 secunde ca sa plantamm o noua planta de tipul acesta
	virtual int GetTime() 
	{
		return 5;
	}

	virtual string GetName() const override
	{
		return "P";
	}

	// daca e ready trage
	bool virtual IsReady()
	{
		if (this->Update_Cycle % Threeshold_Shot == 0)
		{
			return true;
		}
		return false;
	}

	Peashooter() = default;

	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect)
	{
		TerrainEntity::Draw(x1, y1, x2, y2);
		if (DrawRect == true)
		{
			Utils::BCX_Rectangle_Console(x1, y1, x2, y2);
			Utils::BCX_DrawNumber_Console(x1 + 45, y1 + 35, GetName());
		}
		else
		{
			Utils::BCX_DrawNumber_Console(x1 + 80, y1 +70, GetName());
		}
	}

	virtual int GetCost() const 
	{
		return 100;
	}

	virtual int GetType() const
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
		return new Peashooter(this->x, this->y, this->pInstanceStateMachine);
	}

	virtual void SpecialEfect() override;
};

class WallNut : public Plant
{
	// Poate fi mancata de maxim 20 ori. Nuca e tare
	int m_damage = 20;

public:

	virtual int GetCost() const
	{
		return 50;
	}

	virtual bool Damage()
	{
		this->m_damage--;
		if (this->m_damage <= 0)
			return true;
		return false;
	}

	virtual int GetType() const
	{
		return 1;
	}
	// Asteptam 5 secunde ca sa plantamm o noua planta de tipul acesta
	virtual int GetTime()
	{
		return 10;
	}

	virtual void Draw(int x1, int y1, int x2, int y2, bool DrawRect)
	{
		TerrainEntity::Draw(x1, y1, x2, y2);
		if (DrawRect == true)
		{
			Utils::BCX_Rectangle_Console(x1, y1, x2, y2);
			Utils::BCX_DrawNumber_Console(x1 + 45, y1 + 35, GetName());
		}
		else
		{
			Utils::BCX_DrawNumber_Console(x1 + 80, y1 + 70, GetName());
		}
	}
	virtual string GetName() const override
	{
		return "W";
	}
	// WallNut is always ready
	bool virtual IsReady()
	{
		return true;
	}

	virtual TerrainEntity* Copy()
	{
		return new WallNut();
	}
};