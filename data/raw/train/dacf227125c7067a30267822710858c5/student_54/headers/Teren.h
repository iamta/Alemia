#pragma once
class Teren
{
private:
	Teren() {}
	~Teren() {}
	static Teren*instance;
	static int columns;
	static int rows;
	static int x_max;
	static int y_max;

public:
	static Teren &getInstance();
	static void destroyInstance();
	void generate_score();
	void Generate_sun_field();
	void Generate_flower_field();
	void Generate_plants();
	void Generate_battlefield(int linii_lupta);
	void Clear_field();

};

