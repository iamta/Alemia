#pragma once
class Resources
{
private:
	
	char sun = '*';
	char sun_positioning[9];
	int free_spaces[9];

public:
	void Generate_sun(int existed_sunflowers);
	Resources();
	~Resources();
	bool check_resource(int y);
};

