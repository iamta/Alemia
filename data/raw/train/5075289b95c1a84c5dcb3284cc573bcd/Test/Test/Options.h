#pragma once




class Options
{
private:
	int level;
	const char* filename = "Level.op";
	
public:
	Options();
	~Options();
	void SetLevel(int level);
	int GetLevel();

};
