#pragma once
#include <vector>
#include <string>
using namespace std;
enum class  Operation
{
	Idle = 0, // la fiecare pas al loopului infinit trebuie sa randam scena
	Click = 1, // eveniment de dublu click..poate ave m sori de colectat
};

class UserAction
{
protected:
	
	Operation operation;

	vector<string> m_params;
public:
	void SetOperation(Operation operation) { this->operation = operation; };

	Operation GetOperation()const { return this->operation; };

	void AddParam(string param) {
		this->m_params.push_back(param);
	}

	UserAction()
	{
		operation = Operation::Idle;
	}

	string operator[](int index)
	{
		return m_params[index];
	}
};

