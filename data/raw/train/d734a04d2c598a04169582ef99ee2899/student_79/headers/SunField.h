#pragma once
#include <array>
#include "Field.h"

class SunField : public Field
{
private:
	static SunField* instance;
	std::array<int, 8> sun_array;
public:

	SunField();
	~SunField();
	const void print_field() const;
	void print_sun(int pos);
	int get_available_sun(int pos) { return sun_array[pos - 1]; };
	void set_available_sun(int pos) { sun_array[pos - 1] = 0; };

	static SunField* GetInstance();
	SunField& operator=(const SunField&);
};

