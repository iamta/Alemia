#pragma once
#include <string>
#include <windows.h>    // Win32API Header File
#include <cstring>
#include <cstdio>
#include "IGame.h"
#include "UserAction.h"
#include "GameStateMachine.h"
#include "Utils.h"
#include "Resource.h"
using namespace std;
//folosesc ConsoleGame in loc de Game pt ca am avut o clasa initiala pe care mi-a fost mai usor sa o schimb decat sa o modific :)

class ConsoleGame : IGame
{
protected:
	int m_rows;
	int m_columns;
	string m_name;
	int m_level;
	GameStateMachine* m_game_state_machine;
	vector<Operation> m_allowed_actions;

public:
	void Start() override;
	bool Update(UserAction new_action) override;
	void End() override {}
	ConsoleGame(string name, int rows, int columns);
protected:
	virtual bool RenderScene();
};