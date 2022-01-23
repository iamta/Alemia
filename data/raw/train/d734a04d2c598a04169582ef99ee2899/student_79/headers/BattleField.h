#pragma once
#include <array>
#include "Field.h"
class BattleField : Field
{
private:
	static BattleField* instance;

	std::array<std::array<int, 9>, 5> battle_field{ 0 };
public:
	BattleField();
	~BattleField();
	const void print_field() const;
	int get_field_position(int m, int n);
	void set_field_position(int m, int n);
	

	static BattleField* GetInstance();
	BattleField& operator=(const BattleField&);
};

